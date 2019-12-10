/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_
    #include "UdpSocket.hpp"
    #include "TcpSocket.hpp"
    #include "TcpServer.hpp"
    #include "CallThread.hpp"
    #include <QObject>
    #include <vector>


    namespace babel {
        class Core : public QObject {
            Q_OBJECT

        public:
            struct Packet {
                char _opcode;
                int _size;
                std::string _data;
            };
        
        public:
            struct User {
                User(std::string username, std::string ip);
                std::string _username;
                std::string _ip;
            };

        public:
            explicit Core(QObject *parent);

        signals:
            void stateChanged(int state);
            void updateUsers(std::string data);
            void updateFriends(std::string data);
            void updateChat(std::string data, bool insert);
            void loggedIn();

        public slots:
            void disconnected();
            void newConnection();
            void readClient();
            void readServer();
            void login();

        public:
            void getAllConnectedUsers(std::string data);
            void connectToTarget(std::string ip);
            void connectToServer(std::string ip, std::string username, std::string password, char input);
            void acceptIncommingCall();
            void finishCall();
            void addFriend(const std::string &username) const;
            void removeFriend(const std::string &username) const;
            void sendMessage(std::string content, std::string recipient, std::string username);
            void requestMessage(std::string content, std::string recipient, std::string username);

        private:
            void acceptedCall();
            void startAudio();
            void startCall();
            void stopCall();
            void stopAudio();
            babel::Core::Packet getNextMessage(char *buffer);

        private:
            CallThread _thread;
            network::TcpServer *_server;
            network::TcpSocket *_socket_server = nullptr;
            network::TcpSocket *_socket_target;
            std::vector<User> _users;
            bool _isCallRunning = false;
            bool _isAudioRunning = false;

            std::string _username;
            std::string _password;
            char _input;
        };
    }
#endif