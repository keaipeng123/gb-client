#include "mainwindow.h"

#include <QStackedWidget>

#include <json/json.h>

#include "catalogpage.h"
#include "sipdef.h"
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

    // 发送命令的辅助函数
    // 协议格式: [4字节 cmd] [4字节 payload长度] [payload字节]
    auto sendCommand = [this](quint32 cmd, const QString &payload = {}) {
        QByteArray data;
        data.append(reinterpret_cast<const char *>(&cmd), sizeof(cmd));
        const QByteArray payloadBytes = payload.toUtf8();
        const quint32 payloadLen = static_cast<quint32>(payloadBytes.size());
        data.append(reinterpret_cast<const char *>(&payloadLen), sizeof(payloadLen));
        if (!payloadBytes.isEmpty()) {
            data.append(payloadBytes);
        }
        tcpClient->sendData(data);
    };

    //TCP客户端信号
    connect(tcpClient, &TcpClient::connected, this, [this, sendCommand]() {
        catalogPage->showStatus(QStringLiteral("已连接到服务器"));
        sendCommand(Command_Session_Register);
    });
    connect(tcpClient, &TcpClient::disconnected, this, [this]() {
        catalogPage->showStatus(QStringLiteral("与服务器连接已断开"), true);
    });
    connect(tcpClient, &TcpClient::reconnecting, this, [this]() {
        catalogPage->showStatus(QStringLiteral("连接断开，正在重连..."), true);
    });
    connect(tcpClient, &TcpClient::dataReceived, this, [this](const QByteArray &data) {
        if (data.size() < 4)
            return;

        const QByteArray jsonData = data.mid(4);

        // hex dump
        QString hexDump;
        hexDump += QStringLiteral("==== 收到 (%1 字节) ====\n").arg(data.size());
        hexDump += QStringLiteral("Hex: ");
        for (int i = 0; i < data.size(); ++i) {
            hexDump += QStringLiteral("%1 ").arg(static_cast<unsigned char>(data[i]), 2, 16, QLatin1Char('0'));
        }
        hexDump += QStringLiteral("\nJSON: ") + QString::fromUtf8(jsonData);
        catalogPage->showStatus(hexDump);

        // 根据响应类型分发
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(jsonData.toStdString(), root))
            return;

        if (root.isMember("subDomain")) {
            catalogPage->updateTree(jsonData);
        } else if (root.isMember("catalog")) {
            catalogPage->updateCatalogTree(currentSipId_, jsonData);
        }
    });
    connect(tcpClient, &TcpClient::errorOccurred, this, [this](const QString &error) {
        catalogPage->showStatus(QStringLiteral("连接失败: %1").arg(error), true);
    });

    // 点击"媒体目录" → 刷新设备列表
    connect(catalogPage, &CatalogPage::refreshRequested, this, [this, sendCommand]() {
        sendCommand(Command_Session_Register);
    });

    // 点击 sipId 节点 → 获取目录
    connect(catalogPage, &CatalogPage::sipIdClicked, this, [this, sendCommand](const QString &sipId) {
        currentSipId_ = sipId;
        sendCommand(Command_Session_Catalog, sipId);
    });

    // 点击摄像头节点 → 请求开流播放
    connect(catalogPage, &CatalogPage::playRequested, this, [this, sendCommand](const QString &sipId, const QString &deviceId) {
        currentSipId_ = sipId;
        sendCommand(Command_Session_RealPlay, deviceId);
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
