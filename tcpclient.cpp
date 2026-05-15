#include "tcpclient.h"

#include <QTcpSocket>
#include <QTimer>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
    , reconnectTimer(new QTimer(this))
{
    reconnectTimer->setSingleShot(true);
    connect(reconnectTimer, &QTimer::timeout, this, [this]() {
        reconnecting_ = true;
        socket->connectToHost(serverIp_, serverPort_);
    });

    connect(socket, &QTcpSocket::connected, this, [this]() {
        reconnecting_ = false;
        reconnectTimer->stop();
        emit connected();
    });

    connect(socket, &QTcpSocket::disconnected, this, [this]() {
        if (autoReconnect_) {
            reconnecting_ = true;
            emit reconnecting();
            reconnectTimer->start(3000);
        } else {
            emit disconnected();
        }
    });

    connect(socket, &QTcpSocket::readyRead, this, [this]() {
        const QByteArray data = socket->readAll();
        emit dataReceived(data);
        emit messageReceived(QString::fromUtf8(data));
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        lastError_ = socket->errorString();
        if (reconnecting_ || autoReconnect_) {
            // 首次连接失败也进入重连流程
            if (!reconnecting_) {
                reconnecting_ = true;
                emit reconnecting();
            }
            reconnectTimer->start(3000);
        } else {
            emit errorOccurred(lastError_);
        }
    });
}

TcpClient::~TcpClient() = default;

void TcpClient::connectToServer(const QString &ip, quint16 port)
{
    serverIp_ = ip;
    serverPort_ = port;
    autoReconnect_ = true;
    reconnecting_ = false;
    reconnectTimer->stop();
    socket->connectToHost(ip, port);
}

void TcpClient::sendMessage(const QString &message)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(message.toUtf8());
    }
}

void TcpClient::sendData(const QByteArray &data)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(data);
    }
}

void TcpClient::disconnectFromServer()
{
    autoReconnect_ = false;
    reconnecting_ = false;
    reconnectTimer->stop();
    socket->disconnectFromHost();
}

QString TcpClient::lastError() const
{
    return lastError_;
}
