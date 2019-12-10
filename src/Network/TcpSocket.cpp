/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** TcpSocket
*/

#include "TcpSocket.hpp"
#include "Core.hpp"
#include <iostream>

babel::network::TcpSocket::TcpSocket(std::string target_ip, int target_port, bool isSocketServer, babel::Core *parent):
    QObject(parent)
{
    _socket = new QTcpSocket(this);

    if (!isSocketServer) {
        connect(_socket, SIGNAL(readyRead()), parent, SLOT(readClient()));
        connect(_socket, SIGNAL(disconnected()), parent, SLOT(disconnected()));
    } else {
        connect(_socket, SIGNAL(readyRead()), parent, SLOT(readServer()));
        connect(_socket, SIGNAL(connected()), parent, SLOT(login()));
        connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    }
    connect(_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    _socket->connectToHost(target_ip.data(), target_port);
}

babel::network::TcpSocket::TcpSocket(QTcpSocket *socket, babel::Core *parent):
    QObject(parent)
{
    _socket = socket;
    connect(_socket, SIGNAL(disconnected()), parent, SLOT(disconnected()));
    connect(_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(_socket, SIGNAL(readyRead()),parent, SLOT(readClient()));
}

void babel::network::TcpSocket::write(const char *buffer, const unsigned int size) const
{
    _socket->write(buffer, size);
}

void babel::network::TcpSocket::read(char *buffer, int size)
{
    _socket->read(buffer, size);
}

std::string babel::network::TcpSocket::getPeerAddress()
{
    return (_socket->peerAddress().toString().toStdString());
}

void babel::network::TcpSocket::close()
{
    _socket->disconnectFromHost();
}

void babel::network::TcpSocket::connected()
{
    qDebug() << "connected...";
}

void babel::network::TcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void babel::network::TcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}
