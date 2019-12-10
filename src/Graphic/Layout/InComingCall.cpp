/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Incoming
*/

#include "InComingCall.hpp"
#include "QString"

babel::graphic::InComingCall::InComingCall(QWidget *parent): QWidget(parent)
{
    _layout = new QHBoxLayout(this);
    _accept = new QPushButton(QIcon("assets/accept.png"), (QString("Accept")));
    _decline = new QPushButton(QIcon("assets/decline.png"), (QString("Decline")));

    _accept->setIconSize(QSize(60, 60));
    _decline->setIconSize(QSize(60, 60));
    connect(_decline, SIGNAL(clicked()), parent, SLOT(stopCall()));
    connect(_accept, SIGNAL(clicked()), parent, SLOT(acceptCall()));
    _layout->addWidget(_decline);
    _layout->addWidget(_accept);
     _player = new QSound("assets/call.wav");
    _player->play();
    _player->setLoops(QSound::Infinite);
}

babel::graphic::InComingCall::~InComingCall()
{
    delete _player;
    delete _layout;
    delete _decline;
    delete _accept;
}
