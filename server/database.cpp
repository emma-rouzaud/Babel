/*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** database
*/

#include "database.hpp"

Database::Database()
{
    int rc = sqlite3_open("users.db", &_db);

    if( rc ) {
        std::cout << "Can't open database" << std::endl;
        exit(84);
    }
    const char *sql = "create table if not exists USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT, USERNAME TEXT NOT NULL, PSWD TEXT NOT NULL, CONTACTS TEXT);";
    if (executeSQLStatement(sql, SQLEmptyCallback) == false) {
        exit(84);
    }
    const char *sql2 = "CREATE TABLE IF NOT EXISTS Message ( id INTEGER PRIMARY KEY AUTOINCREMENT, sender VARCHAR(40) NOT NULL, recipient VARCHAR(40) NOT NULL, content TEXT NOT NULL, sending_date DATETIME NOT NULL);";
    if (executeSQLStatement(sql2, SQLEmptyCallback) == false) {
        exit(84);
    }
}

Database::~Database()
{
    sqlite3_close(_db);
}

std::string Database::getUsername()
{
    return (_username);
}

std::string Database::getPswd()
{
    return (_pswd);
}

std::string Database::getMessageHistory()
{
    return (_messageHistory);
}

void Database::userIsFound()
{
    _found = true;
}

void Database::setContactList(std::string contactList)
{
    _contactList = contactList;
}

void Database::setMessageHistory(std::string message)
{
    _messageHistory = message + _messageHistory;
}

std::string Database::getMessage()
{
    return (_error);
}

bool Database::getExistingContact(std::string username)
{
    std::string sql = "SELECT CONTACTS from USERS WHERE USERNAME = '" + username + "';";
    if (executeSQLStatement(sql.c_str(), SQLContactCallback) == false) {
        return (false);
    }
    return (true);
}

bool Database::updateContact(std::string contact, std::string username)
{
    std::string sql2 = "UPDATE USERS SET CONTACTS = '" + contact + "' WHERE USERNAME = '" + username + "';";
    if (executeSQLStatement(sql2.c_str(), SQLEmptyCallback) == false) {
        return (false);
    }
    return (true);
}

bool Database::getUsernameAndPassword(int (callback)(void *, int , char **, char **))
{
    const char *sql = "SELECT USERNAME,PSWD from USERS";
    if (executeSQLStatement(sql, callback) == false) {
        return (false);
    }
    return (true);
}

bool Database::InsertNewUser(std::string username, std::string pswd)
{
    std::string sql2 = "INSERT INTO USERS (USERNAME,PSWD) VALUES ('" + username + "', '" + pswd + "');";
    if (executeSQLStatement(sql2.c_str(), SQLEmptyCallback) == false) {
        return (false);
    }
    return (true);
}

bool Database::selectChatMessages(std::string sender, std::string recipient, std::string nb)
{
    _error = "";
    _messageHistory = "";
    std::string sql = "SELECT id, sender, recipient, content FROM (SELECT id, sender, recipient, content, sending_date FROM Message WHERE ((sender='" + sender + "' AND recipient='" + recipient + "') OR (sender='" + recipient + "' AND recipient='" + sender + "')) ORDER BY sending_date DESC LIMIT " + nb + ") AS LastLine ORDER BY sending_date ASC LIMIT 10;";
    if (executeSQLStatement(sql.c_str(), SQLChatCallback) == false) {
        _error = "An Error has occured with the database";
        return (false);
    }
    return (true);
}

bool Database::addChatMessages(std::string sender, std::string recipient, std::string content)
{
    _error = "";
    std::string sql2 = "INSERT INTO Message (sender, recipient, content, sending_date) VALUES (\"" + sender + "\", \"" + recipient +  "\", \"" + content + "\", CURRENT_TIMESTAMP);";
    if (executeSQLStatement(sql2.c_str(), SQLEmptyCallback) == false) {
        _error = "An Error has occured with the database";
        return (false);
    }
    return (true);
}

bool Database::addFriend(std::string username, std::string newFriend)
{
    _error = "";
    _contactList = "";
    if (getExistingContact(username) == false) {
        _error = "An Error has occured with the database";
        return (false);
    }
    std::string tmp = ";" + _contactList;
    if (tmp.find(";" + newFriend + ";") != std::string::npos) {
        _error = "User is already in your contacts";
        return (false);
    }
    if (updateContact(_contactList + newFriend + ";", username) == false) {
        _error = "An Error has occured with the database";
        return (false);
    }
    return (true);
}

bool Database::removeFriend(std::string username, std::string newFriend)
{
    _error = "";
    _contactList = "";
    if (getExistingContact(username) == false) {
        _error = "An Error has occured with the database";
        return (false);
    }
    std::string tmp = ";" + _contactList;
    std::size_t pos = tmp.find(";" + newFriend + ";");
    if (pos == std::string::npos) {
        _error = "User is not in your contacts";
        return (false);
    }
    _contactList.erase(pos, newFriend.size() + 1);
    if (updateContact(_contactList, username) == false) {
        _error = "An Error has occured with the database";
        return (false);
    }
    return (true);
}

bool Database::checkAuthentication(bool newUser, std::string username, std::string pswd)
{
    _username = username;
    _pswd = pswd;
    _error = "";
    if (newUser) {
        if (getUsernameAndPassword(SQLCreateCallback) == false) {
            _error = "Username already exists";
            return (false);
        }
        if (InsertNewUser(username, pswd) == false) {
            _error = "An Error has occured with the database";
            return (false);
        }
    } else {
        _found = false;
        if (getUsernameAndPassword(SQLLoginCallback) == false || _found == false) {
            _error = "Username or password is incorrect";
            return (false);
        }
    }
    return (true);
}

std::string Database::getContactMessage(std::string username)
{
    if (getExistingContact(username) == false) {
        _error = "An Error has occured with the database";
        return (_error);
    }
    return (_contactList);
}

int Database::SQLEmptyCallback(void *database, int argc, char **argv, char **azColName)
{
    return (0);
}

int Database::SQLLoginCallback(void *database, int argc, char **argv, char **azColName)
{
    std::string username = static_cast<Database*>(database)->getUsername();
    std::string pswd = static_cast<Database*>(database)->getPswd();
    if (argc < 2) {
        return (1);
    }
    if (username == argv[0] && pswd == argv[1]) {
        static_cast<Database*>(database)->userIsFound();
    }
    return (0);
}

int Database::SQLCreateCallback(void *database, int argc, char **argv, char **azColName)
{
    std::string username = static_cast<Database*>(database)->getUsername();
    if (argc < 2 || username == argv[0]) {
        return (1);
    }
    return (0);
}

int Database::SQLContactCallback(void *database, int argc, char **argv, char **azColName)
{
    if (argc < 1) {
        return (1);
    }
    if (argv[0] != nullptr) {
        static_cast<Database*>(database)->setContactList(argv[0]);
        return (0);
    }
    static_cast<Database*>(database)->setContactList("");
    return (0);
}

int Database::SQLChatCallback(void *database, int argc, char **argv, char **azColName)
{
    if (argc < 4) {
        return (1);
    }
    std::string id = argv[0];
    std::string sender = argv[1];
    std::string recipient = argv[2];
    std::string content = argv[3];
    std::string message = id + "$" + sender + "$" + recipient + "$" + content + ";";
    static_cast<Database*>(database)->setMessageHistory(message);
    return (0);
}

bool Database::executeSQLStatement(const char *sql, int (callback)(void *, int , char **, char **))
{
    char *zErrMsg = 0;
    int rc = sqlite3_exec(_db, sql, callback, this, &zErrMsg);
   
    if (rc != SQLITE_OK ) {
        std::cout << "SQL KO: " << zErrMsg << std::endl << std::endl;
        sqlite3_free(zErrMsg);
        return (false);
   }
   std::cout << "SQL OK" << std::endl << std::endl;
    return (true);
}