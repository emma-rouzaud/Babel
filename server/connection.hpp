 /*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** Connection
*/

#ifndef CONNECTION_H
# define CONNECTION_H

#ifdef _WIN32
    #define WINVER 0x0A00
    #define _WIN32_WINNT 0x0A00
    #include <SDKDDKVer.h>
#endif

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>


struct Packet;

class Connection : public boost::enable_shared_from_this<Connection>{
    public:
        ~Connection();
        static boost::shared_ptr<Connection> create(boost::asio::io_context& io_context);
        boost::asio::ip::tcp::socket& getSocket();
        bool isOpen();
        bool isInStandby();
        bool isConnected();
        bool isNewUser();
        bool shouldBeAdded();
        void resetStandby(bool error);
        void resetNewFriend();
        void resetMessageInfo();
        void resetMessageHistory();
        std::string getNewFriend();
        std::string getMessageInfo();
        std::string getMessageHistory();
        std::string getIp();
        std::string getUsername();
        std::string getPswd();
        void sendMessage(Packet packet);
        void receiveMessage();
        void checkMessageReceived();

    private:
        Connection(boost::asio::io_context& io_context);
        void handle_write(const boost::system::error_code&, size_t);
        void handle_read(const boost::system::error_code&, size_t);
        
        boost::asio::ip::tcp::socket _socket;
        std::string _message;
        char _data[1028];
        std::string _username = "";
        std::string _pswd = "";
        bool _open = true;
        bool _standby = false;
        bool _connected = false;
        bool _newUser = -1;
        bool _add = false;
        std::string _messageInfo = "";
        std::string _messageHistory = "";
        std::string _newFriend = "";
};

#endif
