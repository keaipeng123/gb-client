#include "tcpclient.h"

#include <QTcpSocket>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &TcpClient::connected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::disconnected);

    connect(socket, &QTcpSocket::readyRead, this, [this]() {
        const QByteArray data = socket->readAll();
        emit messageReceived(QString::fromUtf8(data));
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        lastError_ = socket->errorString();
        emit errorOccurred(lastError_);
    });
}

TcpClient::~TcpClient() = default;

void TcpClient::connectToServer(const QString &ip, quint16 port)
{
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
    socket->disconnectFromHost();
}

QString TcpClient::lastError() const
{
    return lastError_;
}
