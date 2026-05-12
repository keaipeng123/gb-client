#include "catalogpage.h"

#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>

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
    //调用函数，加载目录树
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

void CatalogPage::populateTree()
{
    //根节点：媒体目录
    auto *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, QStringLiteral("媒体目录"));

    //一级子节点：直播源
    auto *liveGroup = new QTreeWidgetItem(root);
    liveGroup->setText(0, QStringLiteral("直播源"));

    auto *camera1 = new QTreeWidgetItem(liveGroup);
    camera1->setText(0, QStringLiteral("camera_01"));

    auto *camera2 = new QTreeWidgetItem(liveGroup);
    camera2->setText(0, QStringLiteral("camera_02"));

    auto *historyGroup = new QTreeWidgetItem(root);
    historyGroup->setText(0, QStringLiteral("历史记录"));

    auto *sample = new QTreeWidgetItem(historyGroup);
    sample->setText(0, QStringLiteral("sample.mp4"));

    //默认展开所有节点
    ui->treeWidget->expandAll();
}