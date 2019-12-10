/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** MyUDP
*/

#include "UdpSocket.hpp"
#include "Core.hpp"

babel::network::UdpSocket::UdpSocket(const int &port, const std::string &target_ip, const int &target_port, babel::Core *parent) :
    QObject(parent)
{
    QString ip;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++) {
        if(!list[nIter].isLoopback()) {
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol)
                ip = QString(list[nIter].toString());
        }
    }
    QHostAddress local(ip);

    _socket = new QUdpSocket(this);
    _socket->bind(QHostAddress::Any, 8080, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    _socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    _address = QHostAddress(QString(target_ip.data()));
    _port = target_port;
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

babel::network::UdpSocket::UdpSocket(const int &port, babel::CallThread *parent) :
    QObject(parent)
{
    QString ip;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++) {
        if(!list[nIter].isLoopback()) {
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol)
                ip = QString(list[nIter].toString());
        }
    }
    QHostAddress local(ip);
    _socket = new QUdpSocket(this);
    _socket->bind(QHostAddress::Any, 8081, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    _socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    connect(_socket, SIGNAL(readyRead()), parent, SLOT(readyRead()));
}

void    babel::network::UdpSocket::readyRead()
{
    QHostAddress sender;
    quint16 senderPort;

    char buffer[MAX_DATAGRAM_SIZE] = {0};
    _socket->readDatagram(buffer, MAX_DATAGRAM_SIZE, &sender, &senderPort);
}

void    babel::network::UdpSocket::write(const char *buffer, const unsigned int &size) const
{
    _socket->writeDatagram(buffer, size, _address, _port);
}

void    babel::network::UdpSocket::read(char *buffer)
{
    QHostAddress sender;
    quint16 senderPort;
    _socket->readDatagram(buffer, MAX_DATAGRAM_SIZE, &sender, &senderPort);
}


void    babel::network::UdpSocket::setTarget(std::string target, const int &port)
{
    if (target[0] == ':')
        target.erase(0,7);
    _address = QHostAddress(QString(target.data()));
    _port = port;
}

babel::network::UdpSocket::~UdpSocket(){}
