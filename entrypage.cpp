#include "entrypage.h"

#include <QApplication>
#include <QIntValidator>
#include <QMessageBox>
#include <QString>

#include "ui_entrypage.h"

EntryPage::EntryPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EntryPage)//创建界面对象
{
    ui->setupUi(this);//把拖拽设计的所有按钮、输入框显示出来
    ui->portEdit->setValidator(new QIntValidator(1, 65535, this));//给端口输入框设置 “只能输数字”

    connect(ui->confirmButton, &QPushButton::clicked, this, [this]() {//点击确认按钮 → 执行大括号里的逻辑
        const QString ip = ui->ipEdit->text().trimmed();
        const QString portText = ui->portEdit->text().trimmed();

        bool ok = false;
        const int portValue = portText.toInt(&ok);

        if (ip.isEmpty() || !ok) {
            QMessageBox::warning(this, QStringLiteral("输入错误"), QStringLiteral("请输入有效的服务器 IP 和端口。"));
            return;
        }

        emit connectRequested(ip, static_cast<quint16>(portValue));//发出信号
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, [this]() {
        ui->ipEdit->clear();
        ui->portEdit->clear();
        ui->ipEdit->setFocus();//光标回到IP输入框
    });
}

EntryPage::~EntryPage()
{
    delete ui;
}