/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Window
*/

#include "Window.hpp"
#include <QLabel>

babel::graphic::Window::Window(QWidget *parent): QWidget(parent), _core(this), _selectedUser("", "", false, false)
{
    _loginPage = new LoginPage(this);
}

void babel::graphic::Window::startCall()
{
    if (_selectedUser._ip == "") {
        std::cout << "Can't start call without a target" << std::endl;
        return;
    }
    std::cout << "Start Call" << std::endl;
    _right->removeWidget(_widgetCall);
    delete _widgetCall;
    _widgetCall = new babel::graphic::WaitingAnswer(this);
    _right->insertWidget(1, _widgetCall);
    _core.connectToTarget(_selectedUser._ip);
    _calling = true;
}

void babel::graphic::Window::acceptCall()
{
    std::cout << "Accept Call" << std::endl;
    _right->removeWidget(_widgetCall);
    delete _widgetCall;
    _widgetCall = new babel::graphic::CallRunning(this);
    _right->insertWidget(1, _widgetCall);
    _core.acceptIncommingCall();
}

void babel::graphic::Window::stopCall()
{
    _calling = false;
    std::cout << "Stop Call" << std::endl;
    _right->removeWidget(_widgetCall);
    delete _widgetCall;
    _widgetCall = new babel::graphic::Home(this);
    _right->insertWidget(1, _widgetCall);
    _core.finishCall();
}

void babel::graphic::Window::stateChanged(int state)
{
    std::cout << "switch to layout " << state << std::endl;
    _right->removeWidget(_widgetCall);
    delete _widgetCall;
    switch (state) {
        case 1: _widgetCall = new babel::graphic::InComingCall(this); _calling = true; break;
        case 2: _widgetCall = new babel::graphic::CallRunning(this); break;
        case 3: _widgetCall = new babel::graphic::Home(this); break;
        default: _widgetCall = new babel::graphic::Home(this); break;
    }
    _right->insertWidget(1, _widgetCall);
}

void babel::graphic::Window::selectedUserChanged()
{
    if (_calling)
        return;
    _selectedUser = _contactList->getDataSelected();
    _selectedUserLabel->setText(QString(_selectedUser._name.data()));
    _chat->clear();
    requestMessage("10");
}

void babel::graphic::Window::switchList()
{
    if (!_displayFriendList)
        _switch->setText(QString("Display Connected Users"));
    else 
        _switch->setText(QString("Display Friends list"));
    _displayFriendList = !_displayFriendList;
    updateList();
}

void babel::graphic::Window::updateList()
{
    _contactScrollArea->takeWidget();
    delete _contactList;
    if (_displayFriendList)
        _contactList = new babel::graphic::ContactList(_friends, _users, this);
    else 
        _contactList = new babel::graphic::ContactList(_users, _friends, this);

    _contactScrollArea->setWidget(_contactList);
}

void babel::graphic::Window::updateFriendList(std::string data)
{
    std::string::size_type pos = data.find(';');
    std::string username;

    _friends.clear();
    while (pos != std::string::npos) {
        username = data.substr(0, pos);
        data.erase(0, pos + 1);
        _friends.push_back(username);
        pos = data.find(';');
    }
    updateList();
}


void babel::graphic::Window::updateChat(std::string data, bool insert)
{
    std::string::size_type pos = data.find('$');
    std::string content;
    std::string sender;
    std::string recipient;
    int id;

    while (pos != std::string::npos) {
        if (insert) {
            id = std::stoi(data.substr(0,pos));
            data.erase(0, pos + 1);
            pos = data.find("$");
        }
        sender = data.substr(0, pos);
        data.erase(0, pos + 1);
        pos = data.find("$");
        recipient = data.substr(0, pos);
        data.erase(0, pos + 1);
        pos = data.find(";");
        content = data.substr(0, pos);
        data.erase(0, pos + 1);
        pos = data.find("$");
        if (sender != _selectedUser._name && recipient != _selectedUser._name)
            continue;
        if (insert)
            _chat->insertMessage(content, sender != _selectedUser._name, id);
        else
            _chat->addMessage(content, sender != _selectedUser._name);
    }
}

void babel::graphic::Window::updateUsers(std::string data)
{
    std::string::size_type pos = data.find(':');
    std::string username;
    std::string ip;

    _users.clear();
    while (pos != std::string::npos) {
        username = data.substr(0, pos);
        data.erase(0, pos + 1);
        pos = data.find(';');
        ip = data.substr(0, pos);
        data.erase(0, pos + 1);
        if (username != _username)
            _users.push_back(babel::DataUser(username, ip, true, false));
        pos = data.find(':');
    }
    updateList();
}

void babel::graphic::Window::switchToHomePage()
{
    delete _loginPage;
    _widgetCall = new babel::graphic::Home(this);
    _contactScrollArea = std::make_unique<QScrollArea>(this);
    _contactList = new ContactList(_users, _friends, this);
    _chat = new Chat(this);
    _mainLayout = new QHBoxLayout(this);
    _contactScrollArea->setMaximumSize(300, 480);
    _contactScrollArea->setWidget(_contactList);
    _right = new QVBoxLayout();
    _left = new QVBoxLayout();
    _switch = new QPushButton("Display Friends list");
    _selectedUserLabel = new QLabel("");
    _selectedUserLabel->setAlignment(Qt::AlignHCenter);
    QObject::connect(_switch, SIGNAL(clicked()), this, SLOT(switchList()));
    _left->addWidget(_switch);
    _left->addWidget(_contactScrollArea.get());
    _right->addWidget(_selectedUserLabel);
    _right->insertWidget(1, _widgetCall);
    _right->addWidget(_chat);
    _mainLayout->addLayout(_left);
    _mainLayout->addLayout(_right);
}

void babel::graphic::Window::checkInputs(std::string username, std::string password, std::string server, char input)
{
    _username = username;
    _core.connectToServer(server, username, password, input);
}

void babel::graphic::Window::addFriend(std::string username)
{
    _core.addFriend(username);
}

void babel::graphic::Window::removeFriend(std::string username)
{
    _core.removeFriend(username);
}

void babel::graphic::Window::sendMessage(std::string content)
{
    _core.sendMessage(content, _selectedUser._name, _username);
}

void babel::graphic::Window::requestMessage(std::string content)
{
    _core.requestMessage(content, _selectedUser._name, _username);
}