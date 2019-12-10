/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>

babel::Core::Core(QObject *parent): QObject(parent)
{
    connect(this, SIGNAL(stateChanged(int)), parent, SLOT(stateChanged(int)));
    connect(this, SIGNAL(updateUsers(std::string)), parent, SLOT(updateUsers(std::string)));
    connect(this, SIGNAL(updateFriends(std::string)), parent, SLOT(updateFriendList(std::string)));
    connect(this, SIGNAL(updateChat(std::string, bool)), parent, SLOT(updateChat(std::string, bool)));
    connect(this, SIGNAL(loggedIn()), parent, SLOT(switchToHomePage()));
    _server = new babel::network::TcpServer(this);
    babel::network::UdpSocket *socket = new babel::network::UdpSocket(60001, &_thread);
    _thread.setSocket(socket);
}

babel::Core::User::User(std::string username, std::string ip)
: _username(username), _ip(ip)
{

}

void babel::Core::disconnected()
{
    this->stopCall();
}


void babel::Core::newConnection()
{
    _socket_target = new babel::network::TcpSocket(_server->getNewConnection(), this);
    this->startCall();
    emit stateChanged(1);
}

void babel::Core::connectToTarget(std::string target_ip)
{
    this->startCall();
    _socket_target = new babel::network::TcpSocket(target_ip.data(), 8000, false, this);
}

void babel::Core::connectToServer(std::string server_ip, std::string username, std::string password, char input)
{
    _username = username;
    _password = password;
    _input = input;
    if (_socket_server) {
        _socket_server->close();
        delete _socket_server;
    }
    _socket_server = new babel::network::TcpSocket(server_ip, 3653, true, this);

}

void babel::Core::startCall()
{
    if (_isCallRunning)
        return;
    _server->stopListening();
    _isCallRunning = true;
}

void babel::Core::startAudio()
{
    if (!_isCallRunning || _isAudioRunning)
        return;
    _thread.setTarget(_socket_target->getPeerAddress());
    _thread.start();
    _isAudioRunning = true;
}

void babel::Core::stopAudio()
{
    if (!_isAudioRunning)
        return;
    _thread.endCall();
    _isAudioRunning = false;
}

void babel::Core::stopCall()
{
    this->stopAudio();
    if (!_isCallRunning)
        return;
    emit stateChanged(3);
    _socket_target->close();
    _server->startListening();
    _isCallRunning = false;
}

void babel::Core::acceptIncommingCall()
{
    char buffer[2] = {1,0};
    _socket_target->write(buffer, 2);
    this->startAudio();
}

void babel::Core::finishCall()
{
    char buffer[2] = {3,0};
    _socket_target->write(buffer, 2);
    this->stopCall();
}

void babel::Core::acceptedCall()
{
    this->startAudio();
    emit stateChanged(2);
}

void babel::Core::readClient()
{
    char buffer[1024] = {0};
    _socket_target->read(buffer, 1024);
    switch (buffer[0]) {
        case 1: this->acceptedCall(); break;
        case 3: this->stopCall();break;
    }
}

babel::Core::Packet babel::Core::getNextMessage(char *buffer)
{
    babel::Core::Packet message;
    std::string data (buffer + 5);
    message._opcode = buffer[0];
    switch (buffer[0]) {
        case 9:
        case 5:
            message._size = 5;
            return (message);
        case 6:
        case 4:
        case 8:
        case 11:
        case 13:
        case 15:
            message._size = *(reinterpret_cast<int*>(buffer + 1)) + 5;
            message._data =  data.substr(0,(*(reinterpret_cast<int*>(buffer + 1))));
            return (message);
        default: return (message);
    }
}

void babel::Core::readServer()
{
    char buffer[2048] = {0};
    _socket_server->read(buffer, 2048);
    int offset = 0;
    babel::Core::Packet message;
    message = getNextMessage(buffer);
    while (message._opcode != 0) {
        switch (message._opcode) {
            case 5: emit loggedIn(); break;
            case 4: emit updateUsers(message._data); break;
            case 8: emit updateFriends(message._data); break;
            case 11: emit updateFriends(message._data); break;
            case 13: emit updateChat(message._data, false); break;
            case 15: emit updateChat(message._data, true); break;
            default: break;
        }
        offset += message._size;
        message = getNextMessage(buffer + offset);
    }
}

void babel::Core::login()
{
    char opcode[2] = {_input, 0};
    std::string buffer = opcode + _username + ";" + _password;
    _socket_server->write(buffer.data(), buffer.size());
}


void babel::Core::addFriend(const std::string &username) const
{
    char opcode[2] = {7, 0};
    std::string buffer = opcode + username;
    _socket_server->write(buffer.data(), buffer.size());
}

void babel::Core::removeFriend(const std::string &username) const
{
    char opcode[2] = {10, 0};
    std::string buffer = opcode + username;
    _socket_server->write(buffer.data(), buffer.size());
}

void babel::Core::sendMessage(std::string content, std::string recipient, std::string username)
{
    char opcode[2] = {12, 0};
    std::string buffer = opcode + username + "$" + recipient + "$" + content + ";";
    _socket_server->write(buffer.data(), buffer.size());
}

void babel::Core::requestMessage(std::string content, std::string recipient, std::string username)
{
    char opcode[2] = {14, 0};
    std::string buffer = opcode + username + "$" + recipient + "$" + content + ";";
    _socket_server->write(buffer.data(), buffer.size());
}