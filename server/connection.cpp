/*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** connection
*/

#include "connection.hpp"
#include "server.hpp"

Connection::Connection(boost::asio::io_context& io_context): _socket(io_context)
{
}

Connection::~Connection()
{
}

boost::shared_ptr<Connection> Connection::create(boost::asio::io_context& io_context)
{
    return (boost::shared_ptr<Connection>(new Connection(io_context)));
}

bool Connection::isOpen()
{
    return (_open);
}

bool Connection::isInStandby()
{
    return (_standby);
}

bool Connection::isNewUser()
{
    return (_newUser);
}

bool Connection::isConnected()
{
    return (_connected);
}

bool Connection::shouldBeAdded()
{
    return (_add);
}


void Connection::resetStandby(bool error)
{
    _standby = false;
    if (error) {
        _username = "";
        _pswd = "";
    } else {
        _connected = true;
    }
}

void Connection::resetNewFriend()
{
    _newFriend = "";
}

void Connection::resetMessageInfo()
{
    _messageInfo = "";
}

void Connection::resetMessageHistory()
{
    _messageHistory = "";
}

std::string Connection::getNewFriend()
{
    return (_newFriend);
}

boost::asio::ip::tcp::socket& Connection::getSocket()
{
    return (_socket);
}

std::string Connection::getIp()
{
    return (_socket.remote_endpoint().address().to_string());
}

std::string Connection::getUsername()
{
    return (_username);
}

std::string Connection::getMessageInfo()
{
    return (_messageInfo);
}

std::string Connection::getMessageHistory()
{
    return (_messageHistory);
}

std::string Connection::getPswd()
{
    return (_pswd);
}

 void Connection::sendMessage(Packet packet)
{
    std::string sClientIp = _socket.remote_endpoint().address().to_string();
    unsigned short uiClientPort = _socket.remote_endpoint().port();

    std::cout << sClientIp << " " << uiClientPort << std::endl;

    boost::asio::async_write(_socket, boost::asio::buffer(packet.data, packet.size),
        boost::bind(&Connection::handle_write, shared_from_this(),
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::receiveMessage()
{
    _socket.async_read_some(boost::asio::buffer(_data, 1028),
        boost::bind(&Connection::handle_read, shared_from_this(),
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::handle_write(const boost::system::error_code& error, size_t bytes)
{
    if (error)
        std::cout << "error while writing" << std::endl;
    else
        std::cout << "succes while writing " << bytes << " bytes" <<  std::endl;
    
}

void Connection::handle_read(const boost::system::error_code& error, size_t bytes)
{
    if (bytes <= 0 || error) {
        _open = false;
        _socket.close();
    } else {
        _data[bytes] = 0;
        checkMessageReceived();
        receiveMessage();
    }
}

void Connection::checkMessageReceived()
{
    std::string message = _data;
    bool add = false;
    switch (message[0]) {
        case 1: _newUser = true; break;
        case 2: _newUser = false; break;
        case 3: _open = false; return;
        case 7: _newFriend = _data + 1; _add = true; return;
        case 10: _newFriend = _data + 1; _add = false; return;
        case 12: _messageInfo = _data + 1; return;
        case 14: _messageHistory = _data + 1; return;
        default: return;
    }
    int offset = static_cast<int>(message.find(";"));
    if (offset == -1)
        return;
    _data[offset] = '\0';
    _pswd = _data + (offset + 1);
    _username = _data + 1;
    _standby = true;
}