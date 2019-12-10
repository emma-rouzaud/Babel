/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Contact
*/

#include "Contact.hpp"
#include "ContactList.hpp"

namespace babel {
    namespace graphic {
        Contact::Contact(babel::DataUser data, QWidget *parent) : QWidget(parent), _data(data)
        {
            _isSelected = false;

            setBackgroundColor(QColor(DEFAULT_BACKGROUND_COLOR));
            setAutoFillBackground(true);

            createContactCredentialsBox();
            createContactBox();
            this->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));
            connect(this, SIGNAL(addFriend(std::string)), parentWidget()->parentWidget(), SLOT(addFriend(std::string)));
            connect(this, SIGNAL(removeFriend(std::string)), parentWidget()->parentWidget(), SLOT(removeFriend(std::string)));
            connect(this, SIGNAL(callUser()), parentWidget()->parentWidget(), SLOT(startCall()));

        }

        void Contact::ShowContextMenu(const QPoint &pos)
        {
            QPoint globalPos = this->mapToGlobal(pos);
            QMenu myMenu;
            myMenu.addAction("Start call");
            myMenu.addAction("Add as friend");
            myMenu.addAction("Remove friend");
            QAction* selectedItem = myMenu.exec(globalPos);
            if (selectedItem) {
                if (selectedItem->text().toStdString() == "Add as friend")
                    emit addFriend(_data._name);
                if (selectedItem->text().toStdString() == "Remove friend")
                    emit removeFriend(_data._name);
                if (selectedItem->text().toStdString() == "Start call") {
                    mousePressEvent(nullptr);
                    emit callUser();
                }
            } else
                return;
        }

        void    Contact::createContactCredentialsBox(void)
        {
            _credentialsBox = std::make_unique<QVBoxLayout>();
            _nameLabel = std::make_unique<QLabel>(_data._name.data());
            _ipAddressLabel = std::make_unique<QLabel>(_data._ip.data());

            _credentialsBox->addWidget(_nameLabel.get());
            _credentialsBox->addWidget(_ipAddressLabel.get());
        }

        void    Contact::createContactBox(void)
        {
            _contactBox = std::make_unique<QHBoxLayout>(this);
            _isOnlineLabel = std::make_unique<QLabel>();

            std::string path = std::string("assets/") + std::string(_data._isOnline == true ? "green" : "red") + std::string("-dot.png");
            _isOnlineLabel->setPixmap(QPixmap(path.c_str()));

            _contactBox->addWidget(_isOnlineLabel.get());
            if (_data._isFriend) {
                _isFriendLabel = std::make_unique<QLabel>();
                _isFriendLabel->setPixmap(QPixmap("assets/star.png"));
                _contactBox->addWidget(_isFriendLabel.get());
            }
            _contactBox->addLayout(_credentialsBox.get());
            setLayout(_contactBox.get());
        }

        void    Contact::setBackgroundColor(QColor color)
        {
            _palette.setColor(QPalette::Background, color);
            setPalette(_palette);
        }

        void    Contact::select(void)
        {
            _isSelected = true;
            setBackgroundColor(QColor(SELECTED_BACKGROUND_COLOR));
        }

        void    Contact::unselect(void)
        {
            _isSelected = false;
            setBackgroundColor(QColor(DEFAULT_BACKGROUND_COLOR));
        }

        void    Contact::mousePressEvent(QMouseEvent *event)
        {
            static_cast<void>(event);
            
            static_cast<ContactList *>(parentWidget())->unselectContact();
            select();
            static_cast<ContactList *>(parentWidget())->updateSelectedIndex();
        }
    }
}
