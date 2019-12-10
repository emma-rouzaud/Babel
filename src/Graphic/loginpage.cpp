#include "loginpage.hpp"

LoginPage::LoginPage(QWidget *parent): QVBoxLayout(parent)
{
    creation = new QPushButton("Create an account !", parent);
    connection = new QPushButton("Login !", parent);

    QObject::connect(creation, SIGNAL(clicked()), this, SLOT(switchToCreate()));
    QObject::connect(connection, SIGNAL(clicked()), this, SLOT(switchToConnect()));
    QObject::connect(this, SIGNAL(login(std::string, std::string, std::string, char)), parent, SLOT(checkInputs(std::string, std::string, std::string, char)));

    addWidget(creation);
    addWidget(connection);
}

LoginPage::~LoginPage()
{
    if (username)
        username->close();
    if (pswd)
        pswd->close();
    if (server != nullptr)
        server->close();
    if (_creationOK != nullptr)
        _creationOK->close();
}

void LoginPage::switchToCreate()
{
    _creationOK = new QPushButton("OK");
    QObject::connect(_creationOK, SIGNAL(clicked()), this, SLOT(checkInputs()));

    username = new QLineEdit;
    pswd = new QLineEdit;
    server = new QLineEdit;

    QFormLayout *inputLayout = new QFormLayout;

    removeWidget(connection);
    removeWidget(creation);
    delete connection;
    delete creation;

    inputLayout->addRow("Enter username:",username);
    inputLayout->addRow("Enter password:",pswd);
    inputLayout->addRow("Enter Server IP:",server);
    addLayout(inputLayout);
    addWidget(_creationOK);
    input = 1;
}

void LoginPage::switchToConnect()
{
    _creationOK = new QPushButton("OK");
    QObject::connect(_creationOK, SIGNAL(clicked()), this, SLOT(checkInputs()));

    username = new QLineEdit;
    pswd = new QLineEdit;
    server = new QLineEdit;
    pswd->setEchoMode(QLineEdit::Password);
    QFormLayout *inputLayout = new QFormLayout;

    removeWidget(connection);
    removeWidget(creation);
    delete connection;
    delete creation;

    inputLayout->addRow("Enter username:",username);
    inputLayout->addRow("Enter password:",pswd);
    inputLayout->addRow("Enter Server IP:",server);
    addLayout(inputLayout);
    addWidget(_creationOK);
    input = 2;
}

void LoginPage::checkInputs()
{
    emit login(username->text().toStdString(), pswd->text().toStdString(), server->text().toStdString(), input);
}
