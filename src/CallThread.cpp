/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** CallThread
*/

#include "CallThread.hpp"
#include <iostream>
#include "UdpSocket.hpp"

babel::CallThread::CallThread()
{
}

void babel::CallThread::run()
{
    _isCallEnded = false;
    _audioManager.init();
    char buffer[MAX_PACKET_SIZE] = {0};
    int nbBytes = 0;
    while (!_isCallEnded) {
        nbBytes = _audioManager.read(buffer);
        _socket->write(buffer, nbBytes);
    }
    _audioManager.close();
}

void babel::CallThread::endCall()
{
    _isCallEnded = true;
}

void babel::CallThread::setTarget(const std::string &target)
{
    _socket->setTarget(target, 8081);
}


void babel::CallThread::setSocket(network::UdpSocket *socket)
{
    _socket = socket;
}

void babel::CallThread::readyRead()
{
    char buffer[MAX_PACKET_SIZE] = {0};
    _socket->read(buffer);
    _audioManager.write(buffer);
}
