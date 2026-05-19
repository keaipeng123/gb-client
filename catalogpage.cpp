#include "catalogpage.h"

#include <QHeaderView>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <json/json.h>

#include "ui_catalogpage.h"

CatalogPage::CatalogPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CatalogPage)
{
    ui->setupUi(this);
    //左边树控件：设置标题“目录”
    ui->treeWidget->setHeaderLabel(QStringLiteral("目录"));
    //右边显示标签：居中、自动换行
    ui->videoLabel->setAlignment(Qt::AlignCenter);
    ui->videoLabel->setWordWrap(true);

    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, [this](QTreeWidgetItem *item, int) {
        if (updatingTree_)
            return;
        if (item->text(0) == QStringLiteral("媒体目录")) {
            emit refreshRequested();// 点了"媒体目录"根节点 → 发刷新信号
        } else if (item->parent() && item->parent()->text(0) == QStringLiteral("媒体目录")) {
            emit sipIdClicked(item->text(0));// 点了根节点下的子节点（设备ID） → 发 sipId 信号
        } else {
            // 深层目录节点：检查 DeviceID 的第 10-12 位是否为摄像头类型
            const QString deviceId = item->data(0, Qt::UserRole).toString();
            if (deviceId.length() >= 13) {
                const QString typeCode = deviceId.mid(10, 3);
                if (typeCode == QStringLiteral("131") || typeCode == QStringLiteral("132")) {
                    // 向上查找所属的 sipId 节点
                    QTreeWidgetItem *p = item;
                    while (p->parent() && p->parent()->text(0) != QStringLiteral("媒体目录")) {
                        p = p->parent();
                    }
                    emit playRequested(p->text(0), deviceId);
                }
            }
        }
    });
    connect(ui->treeWidget, &QTreeWidget::itemExpanded, this, [this](QTreeWidgetItem *item) {
        if (!updatingTree_ && item->text(0) == QStringLiteral("媒体目录")) {
            emit refreshRequested();//展开"媒体目录"时也刷新
        }
    });

    populateTree();// 最后调用，初始化一个空的"媒体目录"根节点
}

CatalogPage::~CatalogPage()
{
    delete ui;
}

void CatalogPage::setServerInfo(const QString &ip, quint16 port)
{
    const QString text = QStringLiteral("等待播放\n\n服务器: %1\n端口: %2")
                             .arg(ip)
                             .arg(port);

    if (startupInfo_.isEmpty()) {
        ui->videoLabel->setText(text);
        return;
    }

    ui->videoLabel->setText(text + QStringLiteral("\n\n") + startupInfo_);
}

void CatalogPage::setStartupInfo(const QString &text)
{
    startupInfo_ = text;
    if (ui->videoLabel->text() == QStringLiteral("等待播放")) {
        ui->videoLabel->setText(QStringLiteral("等待播放\n\n") + startupInfo_);
    }
}

QLabel *CatalogPage::videoLabel() const
{
    return ui->videoLabel;
}

void CatalogPage::showStatus(const QString &status, bool isError)
{
    if (isError) {
        ui->videoLabel->setStyleSheet(QStringLiteral("color: red;"));
    } else {
        ui->videoLabel->setStyleSheet(QStringLiteral("color: green;"));
    }
    ui->videoLabel->setText(status);
}

void CatalogPage::updateTree(const QByteArray &jsonData)
{
//     {
//   "subDomain": [
//     { "sipId": "34020000001110000001" },
//     { "sipId": "34020000001110000002" }
//   ]
// }
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(jsonData.toStdString(), root)) {
        return;
    }

    const Json::Value &subDomain = root["subDomain"];
    if (!subDomain.isArray()) {
        return;
    }

    updatingTree_ = true;

    ui->treeWidget->clear();

    auto *rootItem = new QTreeWidgetItem(ui->treeWidget);
    rootItem->setText(0, QStringLiteral("媒体目录"));

    for (Json::ArrayIndex i = 0; i < subDomain.size(); ++i) {
        const QString sipId = QString::fromStdString(subDomain[i]["sipId"].asString());
        auto *item = new QTreeWidgetItem(rootItem);// 以 rootItem 为父节点
        item->setText(0, sipId);// 显示文本 = sipId
        item->setData(0, Qt::UserRole, sipId);// 隐藏数据 = sipId
    }

    ui->treeWidget->expandAll();// 4. 展开所有节点

    updatingTree_ = false;
}

void CatalogPage::updateCatalogTree(const QString &sipId, const QByteArray &jsonData)
{

//     {
//   "catalog": [
//     { "DeviceID": "root001", "Name": "根设备", "ParentID": "root001" },
//     { "DeviceID": "ch001",   "Name": "通道1",  "ParentID": "root001" },
//     { "DeviceID": "ch002",   "Name": "通道2",  "ParentID": "root001" }
//   ]
// }

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(jsonData.toStdString(), root))
        return;

    const Json::Value &catalog = root["catalog"];
    if (!catalog.isArray() || catalog.empty())
        return;

    // 找到 "媒体目录" 下的 sipId 节点
    QTreeWidgetItem *mediaRoot = ui->treeWidget->topLevelItem(0);// 获取"媒体目录"
    if (!mediaRoot)
        return;
    // 遍历"媒体目录"的子节点，找到 text 等于 sipId 的那个
    QTreeWidgetItem *sipItem = nullptr;
    for (int i = 0; i < mediaRoot->childCount(); ++i) {
        if (mediaRoot->child(i)->text(0) == sipId) {
            sipItem = mediaRoot->child(i);
            break;
        }
    }
    if (!sipItem)
        return;

    updatingTree_ = true;

    // 清除 sipId 节点的旧子项
    while (sipItem->childCount() > 0) {
        delete sipItem->takeChild(0);
    }

    // 第一遍：创建所有节点
    QHash<QString, QTreeWidgetItem *> itemMap;// deviceId → 树节点 的映射表
    QString rootDeviceId;
    for (Json::ArrayIndex i = 0; i < catalog.size(); ++i) {
        // 为每个 JSON 条目创建一个 QTreeWidgetItem
        const auto &entry = catalog[i];
        const QString deviceId = QString::fromStdString(entry["DeviceID"].asString());
        const QString name     = QString::fromStdString(entry["Name"].asString());
        const QString parentId = QString::fromStdString(entry["ParentID"].asString());

        auto *item = new QTreeWidgetItem();
        item->setText(0, name);
        item->setData(0, Qt::UserRole, deviceId);
        itemMap[deviceId] = item;

        if (deviceId == parentId) {
            rootDeviceId = deviceId;
        }
    }

    // 自引用根节点挂在 sipId 下
    QTreeWidgetItem *catalogRoot = nullptr;
    if (!rootDeviceId.isEmpty()) {
        catalogRoot = itemMap.value(rootDeviceId);
    }
    if (!catalogRoot) {
        catalogRoot = new QTreeWidgetItem();
        catalogRoot->setText(0, sipId);
    }
    sipItem->addChild(catalogRoot);

    // 第二遍：非根节点根据 ParentID 挂载
    for (Json::ArrayIndex i = 0; i < catalog.size(); ++i) {
        const auto &entry = catalog[i];
        const QString deviceId = QString::fromStdString(entry["DeviceID"].asString());
        const QString parentId = QString::fromStdString(entry["ParentID"].asString());

        if (deviceId == rootDeviceId)
            continue;

        auto *item = itemMap.value(deviceId);
        if (!item || item->parent())
            continue;

        auto *parentItem = itemMap.value(parentId);
        if (parentItem && parentItem != item) {
            parentItem->addChild(item);
        } else {
            catalogRoot->addChild(item);
        }
    }

    sipItem->setExpanded(true);//展开设备节点，让用户直接看到下面的目录树
    updatingTree_ = false;
}

void CatalogPage::populateTree()
{
    auto *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, QStringLiteral("媒体目录"));
}