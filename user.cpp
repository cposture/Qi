#include "user.h"


User *User::uniqueUser = new User();

User::User(const QString &username, const QString &passwaord, int id)
    :userName(username)
    ,passwaord(passwaord)
    ,UserID(id)
{
}

const QString& User::getUserName() const
{
    return userName;
}

const QString& User::getPassword() const
{
    return passwaord;
}

void User::setRootFolder(QiFolder *r)
{
    rootFolder = r;
}

User* User::getInstance()
{
    return uniqueUser;
}

void User::setUserName(const QString &n)
{
    userName = n;
}

void User::setPassword(const QString &p)
{
    passwaord = p;
}

void User::setUserID(int id)
{
    UserID = id;
}

int User::getUserID()const
{
    return UserID;
}

