/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Home
*/

#include "Home.hpp"
#include "QString"

babel::graphic::Home::Home(QWidget *parent): QWidget(parent)
{
    _layout = new QHBoxLayout(this);
    _start = new QPushButton(QIcon("assets/accept.png"), (QString(" Start Call")));
    _start->setIconSize(QSize(60, 60));
    connect(_start, SIGNAL(clicked()), parent, SLOT(startCall()));
    _layout->addWidget(_start);

}

babel::graphic::Home::~Home()
{
    delete _layout;
    delete _start;
}