/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Home
*/

#ifndef HOME_HPP_
#define HOME_HPP_

#include <iostream>
#include <memory>

#include <QApplication>
#include <QtWidgets>
#include <QPushButton>

namespace babel {
    namespace graphic {
        class Home : public QWidget {
                Q_OBJECT
            public:
                Home(QWidget *parent);
                ~Home();

            private:
                QPushButton *_start;
                QHBoxLayout *_layout;
        };
    }
}

#endif /* !HOME_HPP_ */
