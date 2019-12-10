/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <QtWidgets>
#include <QApplication>

#include <vector>
#include <iostream>

namespace babel {
    namespace graphic {
        class Message : public QWidget {
            Q_OBJECT
            public:
                Message(std::string message, QWidget *parent = 0);

            public:
                void setBackgroundColor(QColor color);

            signals:

            private:
                QLabel *_content;
                QPalette    _palette;
                QVBoxLayout *_messageBox;
        };
    }
}

#endif /* !CONTACTLIST_HPP_ */
