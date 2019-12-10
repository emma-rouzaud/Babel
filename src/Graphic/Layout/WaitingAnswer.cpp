/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Waiting
*/

#include "WaitingAnswer.hpp"
#include <QString>

babel::graphic::WaitingAnswer::WaitingAnswer(QWidget *parent): QWidget(parent)
{
    _layout = new QHBoxLayout(this);
    _cancel = new QPushButton(QIcon("assets/decline.png"), (QString("Cancel Call")));
    _cancel->setIconSize(QSize(60, 60));
    connect(_cancel, SIGNAL(clicked()), parent, SLOT(stopCall()));
    _layout->addWidget(_cancel);
    _player = new QSound("assets/call.wav");
    _player->play();
    _player->setLoops(QSound::Infinite);
}

babel::graphic::WaitingAnswer::~WaitingAnswer()
{
    delete _layout;
    delete _player;
    delete _cancel;
}
