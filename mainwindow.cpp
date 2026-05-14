#include "mainwindow.h"

#include <QStackedWidget>

#include "catalogpage.h"
#include "entrypage.h"
#include "tcpclient.h"

MainWindow::MainWindow(const QString &startupInfo, QWidget *parent)
    : QMainWindow(parent)
    , stack(new QStackedWidget(this))
    , entryPage(new EntryPage(this))
    , catalogPage(new CatalogPage(this))
    , tcpClient(new TcpClient(this))
{
    setWindowTitle(QStringLiteral("HelloQt Client"));//窗口标题
    resize(1100, 700);//窗口大小

    catalogPage->setStartupInfo(startupInfo);//把版本信息传给内容页面

    stack->addWidget(entryPage);//将两个页面添加到页面切换器中
    stack->addWidget(catalogPage);
    stack->setCurrentWidget(entryPage);//默认显示登录页面
    setCentralWidget(stack);//整个窗口里只显示这个 "页面切换器"

    //当登录页面（entryPage）发出 "我要连接服务器（connectRequested）" 信号时 主窗口（MainWindow）就执行 "处理连接（handleConnectRequested）" 函数
    connect(entryPage, &EntryPage::connectRequested, this, &MainWindow::handleConnectRequested);

    //TCP客户端信号
    connect(tcpClient, &TcpClient::connected, this, [this]() {
        catalogPage->showStatus(QStringLiteral("已连接到服务器"));
        quint32 cmd = 1;
        QByteArray data;
        data.append(reinterpret_cast<const char *>(&cmd), sizeof(cmd));
        tcpClient->sendData(data);
    });
    connect(tcpClient, &TcpClient::disconnected, this, [this]() {
        catalogPage->showStatus(QStringLiteral("与服务器连接已断开"), true);
    });
    connect(tcpClient, &TcpClient::messageReceived, this, [this](const QString &message) {
        catalogPage->showStatus(QStringLiteral("收到消息: %1").arg(message));
    });
    connect(tcpClient, &TcpClient::errorOccurred, this, [this](const QString &error) {
        catalogPage->showStatus(QStringLiteral("连接失败: %1").arg(error), true);
    });
}

void MainWindow::handleConnectRequested(const QString &ip, quint16 port)
{
    //把用户输入的 IP + 端口 传给内容页面，并切换到内容页面
    catalogPage->setServerInfo(ip, port);
    stack->setCurrentWidget(catalogPage);
    //连接TCP服务器
    tcpClient->connectToServer(ip, port);
}
