/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Message
*/

#include "Message.hpp"

babel::graphic::Message::Message(std::string message, QWidget *parent): QWidget(parent)
{
    _messageBox = new QVBoxLayout(this);
    _content = new QLabel(message.data());
    _messageBox->addWidget(_content);
    setAutoFillBackground(true);
}

void  babel::graphic::Message::setBackgroundColor(QColor color)
{
    _palette.setColor(QPalette::Background, color);
    setPalette(_palette);
}