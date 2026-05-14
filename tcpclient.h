#pragma once

#include <QObject>

class QTcpSocket;

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
    void errorOccurred(const QString &error);

private:
    QTcpSocket *socket;
    QString lastError_;
};
