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
        if (item->text(0) == QStringLiteral("媒体目录")) {
            emit refreshRequested();
        }
    });

    populateTree();
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
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(jsonData.toStdString(), root)) {
        return;
    }

    const Json::Value &subDomain = root["subDomain"];
    if (!subDomain.isArray()) {
        return;
    }

    ui->treeWidget->clear();

    auto *rootItem = new QTreeWidgetItem(ui->treeWidget);
    rootItem->setText(0, QStringLiteral("媒体目录"));

    for (Json::ArrayIndex i = 0; i < subDomain.size(); ++i) {
        const QString sipId = QString::fromStdString(subDomain[i]["sipId"].asString());
        auto *item = new QTreeWidgetItem(rootItem);
        item->setText(0, sipId);
    }

    ui->treeWidget->expandAll();
}

void CatalogPage::populateTree()
{
    auto *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, QStringLiteral("媒体目录"));
}