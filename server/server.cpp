/*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** server
*/

#include "server.hpp"

Server::Server(boost::asio::io_context& io_context): _io_context(io_context), _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3653))
{
    _db = new Database();
    
    waitForConnection();
    while (1) {
        _io_context.poll();
        checkForServerUpdates();
    }
}

Server::~Server()
{
}

Packet Server::FormatMessage(std::string message, char opcode)
{
    Packet packet;
    char *final = reinterpret_cast<char *>(malloc(sizeof(char) * (5 + message.size())));
    final[0] = opcode;
    MessageSize size;
    size.size = message.size();
    for (int i = 0; i < 4 ; i += 1)
        final[i + 1] = size.bytes[i];
    message.copy(final + 5, message.size());
    packet.size = 5 + size.size;
    packet.data = final;
    return (packet);
}

void Server::handleNewConnections(std::vector<boost::shared_ptr<Connection>>::iterator it)
{
    Packet packet;

    if (_db->checkAuthentication(it->get()->isNewUser(), it->get()->getUsername(), it->get()->getPswd())) {
        _update = true;
        it->get()->resetStandby(false);
        packet = FormatMessage(_db->getMessage(), 5);
        it->get()->sendMessage(packet);
        packet = FormatMessage(_db->getContactMessage(it->get()->getUsername()), 8);
        it->get()->sendMessage(packet);
    } else {
        it->get()->resetStandby(true);
        packet = FormatMessage(_db->getMessage(), 6);
        it->get()->sendMessage(packet);
    }
}

void Server::handleFriendRequests(std::vector<boost::shared_ptr<Connection>>::iterator it)
{
    Packet packet;

    if (it->get()->shouldBeAdded()) {
        if (_db->addFriend(it->get()->getUsername(), it->get()->getNewFriend())) {
            packet = FormatMessage(_db->getMessage(), 9);
            it->get()->sendMessage(packet);
            packet = FormatMessage(_db->getContactMessage(it->get()->getUsername()), 8);
            it->get()->sendMessage(packet);
        } else {
            packet = FormatMessage(_db->getMessage(), 6);
            it->get()->sendMessage(packet);
        }
    } else {
        if (_db->removeFriend(it->get()->getUsername(), it->get()->getNewFriend())) {
            packet = FormatMessage(_db->getMessage(), 11);
            it->get()->sendMessage(packet);
            packet = FormatMessage(_db->getContactMessage(it->get()->getUsername()), 8);
            it->get()->sendMessage(packet);
        } else {
            packet = FormatMessage(_db->getMessage(), 6);
            it->get()->sendMessage(packet);
        }
    }
    it->get()->resetNewFriend();
}

std::vector<boost::shared_ptr<Connection>>::iterator Server::findUser(std::string username)
{
    for (auto it = _users.begin() ; it != _users.end(); it++) {
        if (it->get()->getUsername() == username) {
            return (it);
        }
    }
    return (_users.end());
}

void Server::handleMessageHistory(std::vector<boost::shared_ptr<Connection>>::iterator it)
{
    Packet packet;
    std::string info = it->get()->getMessageHistory();
    std::size_t pos = 0;

    pos = info.find("$");
    std::string sender = info.substr(0, pos);
    info.erase(0, pos + 1);
    pos = info.find("$");
    std::string recipient = info.substr(0, pos);
    info.erase(0, pos + 1);
    pos = info.find(";");
    std::string nb = info.substr(0, pos);
    if (_db->selectChatMessages(sender, recipient, nb)) {
        packet = FormatMessage(_db->getMessageHistory(), 15);
        it->get()->sendMessage(packet);
    } else {
        packet = FormatMessage(_db->getMessage(), 6);
        it->get()->sendMessage(packet);
    }
    it->get()->resetMessageHistory();
}

void Server::handleNewChatMessage(std::vector<boost::shared_ptr<Connection>>::iterator it)
{
    Packet packet;
    std::string info = it->get()->getMessageInfo();
    std::size_t pos = 0;

    pos = info.find("$");
    std::string sender = info.substr(0, pos);
    info.erase(0, pos + 1);
    pos = info.find("$");
    std::string recipient = info.substr(0, pos);
    info.erase(0, pos + 1);
    pos = info.find(";");
    std::string content = info.substr(0, pos);

    if (_db->addChatMessages(sender, recipient, content)) {
        packet = FormatMessage(it->get()->getMessageInfo(), 13);
        it->get()->sendMessage(packet);
        auto user = findUser(recipient);
        if (user != _users.end()) {
            user->get()->sendMessage(packet);
        }
    } else {
        packet = FormatMessage(_db->getMessage(), 6);
        it->get()->sendMessage(packet);
    }
    it->get()->resetMessageInfo();
}

void Server::checkForServerUpdates()
{
    _update = false;

    for (auto it = _users.begin() ; it != _users.end();) {
        if (it->get()->isOpen() == false) {
            if (it->get()->isConnected()) {
                _update = true;
            }
            _users.erase(it);
            continue;
        }
        if (it->get()->isInStandby()) {
            handleNewConnections(it);
        }
        if (it->get()->isConnected() && it->get()->getNewFriend() != "") {
            handleFriendRequests(it);
        }
        if (it->get()->isConnected() && it->get()->getMessageInfo() != "") {
            handleNewChatMessage(it);
        }
        if (it->get()->isConnected() && it->get()->getMessageHistory() != "") {
            handleMessageHistory(it);
        }
        it++;
    }
    if (_update) {
        updateUserList();
    }
}

void Server::updateUserList()
{
    Packet packet;
    _tosend = "";
    for (auto it = _users.begin() ; it != _users.end(); ++it) {
        if (it->get()->isConnected()) {
            _tosend += it->get()->getUsername();
            _tosend += ":";
            _tosend += it->get()->getIp();
            _tosend += ";";
        }
    }
    for (auto it = _users.begin() ; it != _users.end(); ++it) {
        if (it->get()->isConnected()) {
            packet = FormatMessage(_tosend, 4);
            it->get()->sendMessage(packet);
        }
    }
}

std::unique_ptr<Server> Server::create()
{
    boost::asio::io_context io_context;
    return (std::unique_ptr<Server>(new Server(io_context)));
}

void Server::waitForConnection()
{
    std::cout << "Waiting ..." << std::endl;
    boost::shared_ptr<Connection> new_connection = Connection::create(_io_context);
    _acceptor.async_accept(new_connection->getSocket(), boost::bind(&Server::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void Server::handle_accept(boost::shared_ptr<Connection> new_connection, const boost::system::error_code& error)
{
    if (!error) {
        _users.push_back(new_connection);
        new_connection->receiveMessage();
    }
    waitForConnection();
}
