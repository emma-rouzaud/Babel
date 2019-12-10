/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** incoming
*/

#ifndef INCOMINGCALL_HPP_
#define INCOMINGCALL_HPP_

#include <iostream>
#include <memory>

#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QSound>

namespace babel {
    namespace graphic {
        class InComingCall : public QWidget {
                Q_OBJECT
            public:
                InComingCall(QWidget *parent);
                ~InComingCall();

            private:
                QPushButton *_accept;
                QPushButton *_decline;
                QHBoxLayout *_layout;
                QSound *_player;
        };
    }
}

#endif /* !INCOMINGCALL_HPP_ */
