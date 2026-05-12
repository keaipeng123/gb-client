#pragma once

#include <QMainWindow>//Qt 主窗口基类

//前置声明：告诉编译器：这三个类是存在的，先不用看具体实现，加快编译速度
class CatalogPage;
class EntryPage;
class QStackedWidget;
class TcpClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT//Qt 信号槽必备宏

public:
    explicit MainWindow(const QString &startupInfo, QWidget *parent = nullptr);

private:
    void handleConnectRequested(const QString &ip, quint16 port);//处理 “连接服务器” 事件

    QStackedWidget *stack;//页面切换器
    EntryPage *entryPage;
    CatalogPage *catalogPage;
    TcpClient *tcpClient;
};