/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Chat
*/

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <QtWidgets>
#include <QApplication>

#include <vector>
#include <iostream>
#include "Message.hpp"

namespace babel {
    namespace graphic {
        class Chat : public QWidget {
            Q_OBJECT
            public:
                Chat(QWidget *parent = 0);
            
            public:
                void clear();
                void addMessage(std::string message, bool owner);
                void insertMessage(std::string message, bool owner, int id);

            signals:
                void sendMessage(std::string content);
                void requestMessage(std::string content);

            public slots:
                void returnPressed();
                void scrollDown();
                void scrollInsert();
                void sliderMoved(int pos);

            private:
                QScrollArea *_messageArea;
                QWidget *_messageList;
                QVBoxLayout *_messageListBox;
                QVBoxLayout *_chatBox;
                std::vector<Message*> _messages;
                QLineEdit *_input;
                int offset = 0;
                int _id = -1;
        };
    }
}

#endif /* !CONTACTLIST_HPP_ */
