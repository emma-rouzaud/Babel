/*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** server
*/

#ifndef SERVER_H
# define SERVER_H

#include "connection.hpp"
#include "database.hpp"

struct Packet {
        int size;
        char *data;
    };

class Server {
    public:

    union MessageSize {
        int size;
        char bytes[4];
    };

    public:
        ~Server();
        static std::unique_ptr<Server> create();
        std::tuple<std::string, std::string> getLoginPair();
        std::tuple<std::string, std::string> getAddPair();
        void setAddPair(std::string contacts);

    private:
        Server(boost::asio::io_context& io_context);
        void waitForConnection();
        void waitForMessages();
        void checkForServerUpdates();
        std::vector<boost::shared_ptr<Connection>>::iterator findUser(std::string username);
        void handleNewChatMessage(std::vector<boost::shared_ptr<Connection>>::iterator it);
        void handleMessageHistory(std::vector<boost::shared_ptr<Connection>>::iterator it);
        void handleNewConnections(std::vector<boost::shared_ptr<Connection>>::iterator it);
        void handleFriendRequests(std::vector<boost::shared_ptr<Connection>>::iterator it);
        void updateUserList();
        Packet FormatMessage(std::string message, char opcode);
        void handle_accept(boost::shared_ptr<Connection> new_connection, const boost::system::error_code& error);

        boost::asio::io_context& _io_context;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::vector<boost::shared_ptr<Connection>> _users;
        std::string _tosend = "First;";
        Database *_db;
        bool _update = false;
};

#endif