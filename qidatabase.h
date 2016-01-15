#ifndef QIDATABASE_H
#define QIDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "user.h"
#include "qifolder.h"
#include "setting.h"
class QiDatabase
{
public:
    static QiDatabase *getInstance();
    ~QiDatabase(){}
    bool connect();
    QSqlError createAll();
    void init(const QString& t_db
                          , const QString& t_hostName
                          , const QString& t_dbName
                          , const QString& t_userName
                          , const QString& t_password);

    QSqlError addUser(const User& user);
    bool hasUser(const User& user);
    int getUserIDFormDB(User &user);
    void setUserRootFolder(User& user);
    QiFolder *searchRootFolder(int id);
    QSqlError addUserSetting(const UserSetting& s);
    QSqlError addDefaultUserSetting(int userid);
    void loadDataFromWeb();
private:
    static QiDatabase *uniqueQiDatabase;
    QSqlDatabase database;
    QString db;
    QString hostName;
    QString dbName;
    QString userName;
    QString password;
    bool	isConnect;

    QiDatabase(){}
};

#endif // QIDATABASE_H
