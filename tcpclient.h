#pragma once

#include <QObject>

class QTcpSocket;
class QTimer;

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient() override;

    void connectToServer(const QString &ip, quint16 port);//发起连接
    void sendMessage(const QString &message);//发送文本消息
    void sendData(const QByteArray &data);//发送二进制数据
    void disconnectFromServer();//断开连接

    QString lastError() const;//获取最后一次错误信息


signals:
    void connected();//连接成功
    void disconnected();//断开连接
    void messageReceived(const QString &message);//收到文本消息
    void dataReceived(const QByteArray &data);//收到二进制数据
    void errorOccurred(const QString &error);//发生错误
    void reconnecting();//正在重连

private:
    QTcpSocket *socket;// Qt 的 TCP 套接字
    QTimer *reconnectTimer;//重连定时器（断线后等几秒再重连）
    QString lastError_;// 记录最后一次错误信息
    QString serverIp_;//记下服务器地址，重连时要用
    quint16 serverPort_ = 0;
    bool autoReconnect_ = false;//是否自动重连
    bool reconnecting_ = false;//当前是否正在重连中
};
