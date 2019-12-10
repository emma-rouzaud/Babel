/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Running
*/

#include "CallRunning.hpp"
#include "QString"

babel::graphic::CallRunning::CallRunning(QWidget *parent): QWidget(parent)
{
    _layout = new QHBoxLayout(this);
    _finish = new QPushButton(QIcon("assets/decline.png"), (QString("Finish Call")));
    _finish->setIconSize(QSize(60, 60));
    connect(_finish, SIGNAL(clicked()), parent, SLOT(stopCall()));
    _layout->addWidget(_finish);
}

babel::graphic::CallRunning::~CallRunning()
{
    delete _layout;
    delete _finish;
}