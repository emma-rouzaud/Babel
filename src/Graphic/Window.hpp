/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <iostream>
#include <memory>

#include <QApplication>
#include <QtWidgets>
#include "Home.hpp"
#include "CallRunning.hpp"
#include "InComingCall.hpp"
#include "WaitingAnswer.hpp"
#include "Core.hpp"
#include "ContactList.hpp"
#include "loginpage.hpp"
#include "Chat.hpp"

namespace babel {
    namespace graphic {
        class Window : public QWidget {
                Q_OBJECT
            public:
                Window(QWidget *parent = 0);

            signals:

            public slots:
                void startCall();
                void stopCall();
                void acceptCall();
                void stateChanged(int state);
                void updateUsers(std::string data);
                void updateFriendList(std::string data);
                void checkInputs(std::string username, std::string password, std::string server, char input);
                void switchToHomePage();
                void switchList();
                void addFriend(std::string username);
                void removeFriend(std::string username);
                void selectedUserChanged();
                void sendMessage(std::string content);
                void requestMessage(std::string content);
                void updateChat(std::string data, bool insert);

            private:
                void updateList();

            private:
                QWidget *_widgetCall;
                QHBoxLayout *_mainLayout;
                QVBoxLayout *_right;
                QVBoxLayout *_left;
                QPushButton *_switch;
                QLabel *_selectedUserLabel;
                LoginPage *_loginPage;
                babel::Core _core;
                std::unique_ptr<QScrollArea>    _contactScrollArea;
                ContactList *_contactList;
                Chat *_chat;
                bool _displayFriendList = false;
                bool _calling = false;
                std::vector<babel::DataUser> _users;
                babel::DataUser _selectedUser;
                std::vector<std::string> _friends;
                std::string _username;
        };
    }
}

#endif /* !WINDOW_HPP_ */
