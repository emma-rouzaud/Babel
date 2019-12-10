/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** ContactList
*/

#ifndef CONTACTLIST_HPP_
#define CONTACTLIST_HPP_

#include <QtWidgets>
#include <QApplication>

#include <vector>
#include <iostream>
#include "Contact.hpp"

namespace babel {
    namespace graphic {
        class ContactList : public QWidget {
            Q_OBJECT
            public:
                ContactList(std::vector<babel::DataUser> &data, std::vector<std::string> &friends, QWidget *parent = 0);
                ContactList(std::vector<std::string> &friends, std::vector<babel::DataUser> &data, QWidget *parent = 0);

                void    updateUsers(std::vector<babel::DataUser> &newData, std::vector<std::string> &friends);
                void    updateFriends(std::vector<DataUser> &newData, std::vector<std::string> &friends);

                babel::DataUser getDataSelected(void) const;
                void    unselectContact(void) const;
                void    updateSelectedIndex(void);
                bool    isFriend(std::string name, std::vector<std::string> &friends);
                bool    isOnline(std::string name, std::vector<babel::DataUser> &users);
                std::string getIp(std::string name, std::vector<babel::DataUser> &users);

            signals:
                void selectedUserChanged();

            private:
                int    _selectedIndex;

                QVBoxLayout *_contactListBox;
                std::vector<std::unique_ptr<Contact>>   _contactList;
        };
    }
}

#endif /* !CONTACTLIST_HPP_ */
