/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** ContactList
*/

#include "ContactList.hpp"

namespace babel {
    namespace graphic {
        ContactList::ContactList(std::vector<DataUser> &data, std::vector<std::string> &friends, QWidget *parent) : QWidget(parent)
        {
            _selectedIndex = -1;
            _contactListBox = new QVBoxLayout(this);
            updateUsers(data, friends);
            connect(this, SIGNAL(selectedUserChanged()), parent, SLOT(selectedUserChanged()));
        }

        ContactList::ContactList(std::vector<std::string> &friends, std::vector<DataUser> &data, QWidget *parent) : QWidget(parent)
        {
            _selectedIndex = -1;
            _contactListBox = new QVBoxLayout(this);
            updateFriends(data, friends);
            connect(this, SIGNAL(selectedUserChanged()), parent, SLOT(selectedUserChanged()));
        }
        
        void    ContactList::updateUsers(std::vector<DataUser> &newData, std::vector<std::string> &friends)
        {
            for (auto it = _contactList.begin(); it != _contactList.end(); ++it)
                _contactListBox->removeWidget((*it).get());
            _contactList.clear();
            delete _contactListBox;
            for (auto it = newData.begin(); it != newData.end(); ++it) {
                (*it)._isFriend = isFriend((*it)._name, friends);
                _contactList.push_back(std::make_unique<Contact>(
                    *it,
                    this
                ));
            }
            _contactListBox = new QVBoxLayout(this);
            for (auto it = _contactList.begin(); it != _contactList.end(); ++it) {
                _contactListBox->addWidget((*it).get());
                (*it)->setFixedSize(280, 60);
            }
        }

        void    ContactList::updateFriends(std::vector<DataUser> &newData, std::vector<std::string> &friends)
        {
            for (auto it = _contactList.begin(); it != _contactList.end(); ++it)
                _contactListBox->removeWidget((*it).get());
            _contactList.clear();
            delete _contactListBox;
            for (auto it = friends.begin(); it != friends.end(); ++it) {
                _contactList.push_back(std::make_unique<Contact>(
                    babel::DataUser(*it, getIp(*it, newData), isOnline(*it, newData), true),
                    this
                ));
            }
            _contactListBox = new QVBoxLayout(this);
            for (auto it = _contactList.begin(); it != _contactList.end(); ++it) {
                _contactListBox->addWidget((*it).get());
                (*it)->setFixedSize(280, 60);
            }
        }

        bool babel::graphic::ContactList::isFriend(std::string name, std::vector<std::string> &friends)
        {
            for (auto it = friends.begin(); it != friends.end(); ++it) {
                if (*it == name)
                    return (true);
            }
            return (false);
        }

        bool babel::graphic::ContactList::isOnline(std::string name, std::vector<babel::DataUser> &users)
        {
            for (auto it = users.begin(); it != users.end(); ++it) {
                if ((*it)._name == name)
                    return (true);
            }
            return (false);
        }

        std::string babel::graphic::ContactList::getIp(std::string name, std::vector<babel::DataUser> &users)
        {
            for (auto it = users.begin(); it != users.end(); ++it) {
                if ((*it)._name == name)
                    return ((*it)._ip);
            }
            return ("");
        }

        void    ContactList::unselectContact(void) const
        {
            if (_selectedIndex != -1)
                _contactList[_selectedIndex]->unselect();
        }

        void    ContactList::updateSelectedIndex(void)
        {
            for (unsigned int i = 0; i < _contactList.size(); i++) {
                if (_contactList[i]->isSelected() == true) {
                    _selectedIndex = i;
                    emit selectedUserChanged();
                    break;
                }
            }
        }
        babel::DataUser ContactList::getDataSelected(void) const
        {
            for (unsigned int i = 0; i < _contactList.size(); i++)
                if (_contactList[i]->isSelected() == true)
                    return (_contactList[i]->getData());
            return (babel::DataUser("","",false,false));
        }
    }
}