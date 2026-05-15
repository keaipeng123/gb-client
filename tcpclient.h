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

    void connectToServer(const QString &ip, quint16 port);
    void sendMessage(const QString &message);
    void sendData(const QByteArray &data);
    void disconnectFromServer();

    QString lastError() const;

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &message);
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);
    void reconnecting();

private:
    QTcpSocket *socket;
    QTimer *reconnectTimer;
    QString lastError_;
    QString serverIp_;
    quint16 serverPort_ = 0;
    bool autoReconnect_ = false;
    bool reconnecting_ = false;
};
