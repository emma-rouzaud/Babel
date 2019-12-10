#ifndef LOGINPAGE_HPP
#define LOGINPAGE_HPP

#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <iostream>

class LoginPage : public QVBoxLayout
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent);
    ~LoginPage();
//    void clearLayout();

signals:
    void login(std::string username, std::string password, std::string server, char input);

public slots:
    void switchToCreate();
    void switchToConnect();
    void checkInputs();

private:
    QLineEdit *pswd = nullptr;
    QLineEdit *server = nullptr;
    QLineEdit *username = nullptr;
    QPushButton *creation = nullptr;
    QPushButton *connection = nullptr;
    QPushButton *_creationOK = nullptr;
    char input;

};


#endif // LOGINPAGE_HPP
