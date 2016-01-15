#ifndef USER_H
#define USER_H

#include "qifolder.h"
class User
{
public:
    static User* getInstance();
    User(const QString& username, const QString& passwaord, int id);
    ~User(){}
    void setRootFolder(QiFolder *r);
    const QString &getUserName() const;
    const QString &getPassword() const;
    int	getUserID() const;
    void setUserName(const QString&);
    void setPassword(const QString&);
    void setUserID(int id);
private:
    User(){}
    static User *uniqueUser;
    QString userName;
    QString passwaord;
    int	userSettingID;
    QiFolder *rootFolder;
    int UserID;
};

#endif // USER_H
