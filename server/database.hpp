 /*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** Database
*/

#ifndef DATABASE_H
# define DATABASE_H

#ifdef _WIN32
    #define WINVER 0x0A00
    #define _WIN32_WINNT 0x0A00
    #include <SDKDDKVer.h>
#endif

#include <sqlite3.h> 
#include <iostream>
#include <string>

class Database {
    public:
        ~Database();
        Database();
        std::string getUsername();
        std::string getPswd();
        std::string getMessage();
        std::string getMessageHistory();
        void setContactList(std::string contactList);
        void setMessageHistory(std::string contactList);
        void userIsFound();
        void clearOpcode();
        std::string getContactMessage(std::string username);

        bool executeSQLStatement(const char *sql, int (callback)(void *, int , char **, char **));
        static int SQLEmptyCallback(void *NotUsed, int argc, char **argv, char **azColName);
        static int SQLLoginCallback(void *NotUsed, int argc, char **argv, char **azColName);
        static int SQLCreateCallback(void *NotUsed, int argc, char **argv, char **azColName);
        static int SQLContactCallback(void *NotUsed, int argc, char **argv, char **azColName);
        static int SQLChatCallback(void *NotUsed, int argc, char **argv, char **azColName);
        
        bool checkAuthentication(bool newUser, std::string username, std::string pswd);
        bool addFriend(std::string username, std::string newFriend);
        bool selectChatMessages(std::string sender, std::string recipient, std::string nb);
        bool addChatMessages(std::string sender, std::string recipient, std::string content);
        bool removeFriend(std::string username, std::string newFriend);
        bool InsertNewUser(std::string username, std::string pswd);
        bool getUsernameAndPassword(int (callback)(void *, int , char **, char **));
        bool updateContact(std::string contact, std::string username);
        bool getExistingContact(std::string username);

    private:
        sqlite3 *_db;
        std::string _error = "";
        std::string _errorMessage = "";
        std::string _contactList = "";
        std::string _messageHistory = "";
        std::string _username = "";
        std::string _pswd = "";
        bool _found = false;
};

#endif
