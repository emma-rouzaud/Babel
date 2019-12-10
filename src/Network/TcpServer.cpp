/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** TcpServer
*/

#include "TcpServer.hpp"
#include "Core.hpp"

babel::network::TcpServer::TcpServer(babel::Core *parent) :
    QObject(parent)
{
    _server = new QTcpServer(this);

    connect(_server, SIGNAL(newConnection()), parent, SLOT(newConnection()));
    this->startListening();
}

void babel::network::TcpServer::startListening()
{
    if (_server->isListening())
        return;
    if(!_server->listen(QHostAddress::Any, 8000))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void babel::network::TcpServer::stopListening()
{
    _server->close();
    qDebug() << "Server stoped!";
}

QTcpSocket *babel::network::TcpServer::getNewConnection()
{
    qDebug() << "Server got new connection!";
    return(_server->nextPendingConnection());
}