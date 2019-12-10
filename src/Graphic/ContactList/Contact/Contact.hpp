/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Contact
*/

#ifndef CONTACT_HPP_
#define CONTACT_HPP_

#include <QtWidgets>
#include <QLabel>
#include <QSharedPointer>
#include <QMenu>
#include <memory>
#include <iostream>

#define DEFAULT_BACKGROUND_COLOR 230, 230, 230
#define SELECTED_BACKGROUND_COLOR 255, 255, 0

namespace babel {
    
    struct DataUser {
        DataUser(std::string name, std::string ip, bool isOnline, bool isFriend):
        _name(name), _ip(ip), _isOnline(isOnline), _isFriend(isFriend){}
        std::string _name;
        std::string _ip;
        bool _isOnline;
        bool _isFriend;
    };

    namespace graphic {
        class Contact : public QWidget {
            Q_OBJECT
            public:
                Contact(
                    babel::DataUser data,
                    QWidget *parent = 0
                );

                void    createContactCredentialsBox(void);
                void    createContactBox(void);
                babel::DataUser getData(void) const {return(_data);};
                void    setBackgroundColor(QColor color);

                bool    isSelected(void) const {return(_isSelected);};
                void    select(void);
                void    unselect(void);

            signals:
                void addFriend(std::string username);
                void removeFriend(std::string username);
                void callUser();

            public slots:
                void ShowContextMenu(const QPoint&);

            private:
                void    mousePressEvent(QMouseEvent *event) override;

                babel::DataUser _data;

                QPalette    _palette;
                bool        _isSelected;

                std::unique_ptr<QHBoxLayout>    _contactBox;
                std::unique_ptr<QVBoxLayout>    _credentialsBox;
                std::unique_ptr<QLabel>         _isOnlineLabel;
                std::unique_ptr<QLabel>         _isFriendLabel;
                std::unique_ptr<QLabel>         _nameLabel;
                std::unique_ptr<QLabel>         _ipAddressLabel;
        };
    }
}

#endif /* !CONTACT_HPP_ */
