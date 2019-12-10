/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Waiting
*/

#ifndef WAITINGANSWER_HPP_
#define WAITINGANSWER_HPP_

#include <iostream>
#include <memory>

#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QSound>

namespace babel {
    namespace graphic {
        class WaitingAnswer : public QWidget {
                Q_OBJECT
            public:
                WaitingAnswer(QWidget *parent);
                ~WaitingAnswer();

            private:
                QPushButton *_cancel;
                QHBoxLayout *_layout;
                 QSound *_player;
        };
    }
}

#endif /* !WAITINGANSWER_HPP_ */
