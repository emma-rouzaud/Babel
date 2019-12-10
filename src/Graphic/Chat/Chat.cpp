/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Chat
*/

#include "Chat.hpp"

babel::graphic::Chat::Chat(QWidget *parent): QWidget(parent)
{
    _chatBox = new QVBoxLayout(this);
    _messageList = new QWidget();
    _messageList->setContentsMargins(5,10,5,0);
    _messageListBox = new QVBoxLayout(_messageList);
    _messageListBox->setAlignment(Qt::AlignTop);
    _messageArea = new QScrollArea();
    _messageArea->setWidgetResizable(true);
    _input = new QLineEdit;
    _chatBox->addWidget(_messageArea);
    _chatBox->addWidget(_input);
    _messageArea->setWidget(_messageList);
    connect(_messageArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));
    connect(_input, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(this, SIGNAL(sendMessage(std::string)), parent, SLOT(sendMessage(std::string)));
    connect(this, SIGNAL(requestMessage(std::string)), parent, SLOT(requestMessage(std::string)));
}

void babel::graphic::Chat::clear()
{
    for (auto it = _messages.begin(); it != _messages.end(); ++it)
        delete (*it);
    _messages.clear();
    offset = 0;
    _id = -1;
}

void babel::graphic::Chat::addMessage(std::string message, bool owner)
{
    Message *newMessage = new Message(message, this);
    _messages.push_back(newMessage);
    _messageListBox->addWidget(newMessage);
    if (owner)
        newMessage->setBackgroundColor(QColor(190,190, 190));
    else
        newMessage->setBackgroundColor(QColor(230, 230, 230));
    offset += 1;
    QTimer::singleShot(10, this, SLOT(scrollDown()));
}
 
void babel::graphic::Chat::insertMessage(std::string message, bool owner, int id)
{
    if (id >= _id && _id != -1)
        return;
    _id = id;
    Message *newMessage = new Message(message, this);
    _messages.push_back(newMessage);
    _messageListBox->insertWidget(0, newMessage);
    if (owner)
        newMessage->setBackgroundColor(QColor(190,190, 190));
    else
        newMessage->setBackgroundColor(QColor(230, 230, 230));
        
    offset += 1;
    QTimer::singleShot(10, this, SLOT(scrollInsert()));
}

void babel::graphic::Chat::scrollDown()
{
    int max = _messageArea->verticalScrollBar()->maximum();
    _messageArea->verticalScrollBar()->setValue(max);
}

void babel::graphic::Chat::scrollInsert()
{
    _messageArea->verticalScrollBar()->setValue(_messageArea->verticalScrollBar()->value() + _messages.back()->height());
}


void babel::graphic::Chat::sliderMoved(int pos)
{
    if (pos == _messageArea->verticalScrollBar()->minimum()) {
        emit requestMessage(std::to_string(offset + 10));
    }
}

void babel::graphic::Chat::returnPressed()
{
    if (_input->text().toStdString() != "")
        emit sendMessage(_input->text().toStdString());
        // addMessage(_input->text().toStdString());
    _input->setText("");
}