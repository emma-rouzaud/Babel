/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Running
*/

#ifndef CALLRUNNING_HPP_
#define CALLRUNNING_HPP_

#include <iostream>
#include <memory>

#include <QApplication>
#include <QtWidgets>
#include <QPushButton>

namespace babel {
    namespace graphic {
        class CallRunning : public QWidget {
                Q_OBJECT
            public:
                CallRunning(QWidget *parent);
                ~CallRunning();

            private:
                QPushButton *_finish;
                QHBoxLayout *_layout;
        };
    }
}

#endif /* !CALLRUNNING_HPP_ */
