#include "qidatabase.h"
#include <QMessageBox>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
QiDatabase* QiDatabase::uniqueQiDatabase = new QiDatabase();

void QiDatabase::init(const QString& t_db
                      , const QString& t_hostName
                      , const QString& t_dbName
                      , const QString& t_userName
                      , const QString& t_password)
{
    db = t_db;
    hostName = t_hostName;
    dbName = t_dbName;
    userName = t_userName;
    password = t_password;

    database = QSqlDatabase::addDatabase(db);
    database.setHostName(hostName);
    database.setDatabaseName(dbName);
    database.setUserName(userName);
    database.setPassword(password);
    database.setPort(3306);
    if(!connect())
    {
        QMessageBox::critical(0,QObject::tr("Database Error"),QObject::tr("Database connection failed"));
        qDebug() << "Database connection failed";
    }
    if(createAll().type() != QSqlError::NoError)
    {
        QMessageBox::critical(0,QObject::tr("Database Error"),QObject::tr("Database creation failed"));
        qDebug() << "Database creation failed";
    }
}

bool QiDatabase::connect()
{
    if(!database.open())
        return (isConnect = false);
    return (isConnect = true);
}

QSqlError QiDatabase::createAll()
{
    QSqlQuery sqlQuery;
    try
    {
         sqlQuery.exec(
                 "CREATE TABLE IF NOT EXISTS Settings("
                    "SettingID INTEGER  AUTO_INCREMENT PRIMARY KEY,"
                    "AutoSignin boolean,"
                    "RemPassword boolean,"
                    "UserID INTEGER,"
                    "FOREIGN KEY (UserID) REFERENCES User(UserID)"
                 ");");
         sqlQuery.finish();
         sqlQuery.exec(
                 "CREATE TABLE IF NOT EXISTS User("
                     "UserID INTEGER  AUTO_INCREMENT PRIMARY KEY,"
                     "Email VARCHAR(50) NOT NULL UNIQUE,"
                     "Password VARCHAR(50) NOT NULL,"
                 ");");
         sqlQuery.finish();

         sqlQuery.exec(
                     "CREATE TABLE IF NOT EXISTS Folder("
                         "FolderID INTEGER  AUTO_INCREMENT PRIMARY KEY,"
                         "FolderName VARCHAR(255) NOT NULL,"
                         "ParentFolderID INTEGER,"
                         "UserID INTEGER,"
                         "FOREIGN KEY (ParentFolderID) REFERENCES Folder(FolderID),"
                         "FOREIGN KEY (UserID) REFERENCES User(UserID)"
                     ");");
         sqlQuery.finish();

         sqlQuery.exec(
                     "CREATE TABLE IF NOT EXISTS File("
                         "FileID INTEGER  AUTO_INCREMENT PRIMARY KEY,"
                         "FileName VARCHAR(255) NOT NULL UNIQUE,"
                         "FileSize INTEGER NOT NULL,"
                         "UploadTime DATETIME,"
                         "FileType VARCHAR(255),"
                         "FileHash VARCHAR(255),"
                         "FolderID INTEGER,"
                         "FOREIGN KEY (FolderID) REFERENCES Folder(FolderID)"
                     ");");
         sqlQuery.finish();
    }
    catch(...)
    {
             QMessageBox::critical(0, QObject::tr("Database Error"),
                                               sqlQuery.lastError().text());
             return sqlQuery.lastError();
    }
    return QSqlError();
}

QSqlError QiDatabase::addUser(const User &user)
{
    QSqlQuery sqlQuery;
    if(!sqlQuery.prepare(
                "INSERT INTO User(UserID,Email,Password) "
                "VALUES(:UserID,:Email,:Password);"))
    {
        return sqlQuery.lastError();
    }
    sqlQuery.bindValue(":UserID",user.getUserID());
    sqlQuery.bindValue(":Email",user.getUserName());
    sqlQuery.bindValue(":Password",user.getPassword());
    sqlQuery.exec();
    if(!sqlQuery.isActive())
    {
        qDebug() << "hasUser prepare fails";
    }
    return QSqlError();
}

void QiDatabase::setUserRootFolder(User& user)
{
    QSqlQuery sqlQuery;
    QiFolder *root = searchRootFolder(user.getUserID());
    if(root == NULL)
        return;
    int i = 0;
    do{
        sqlQuery.prepare(
                    "SELECT * FROM Folder "
                    "WHERE ParentFolderID=:pid AND UserID=:uid"
                    );
        sqlQuery.bindValue(":pid",0);
        sqlQuery.bindValue(":uid",user.getUserID());
        sqlQuery.exec();
        if(!sqlQuery.isActive())
        {
            qDebug() << "hasUser prepare fails";
        }
        while(sqlQuery.next())
        {
            QiFolder *p = new QiFolder();
            p->setName(sqlQuery.value(1).toString());
            p->setParent(NULL);
            p->setType(QiObject::FOLDER);
            p->setID(sqlQuery.value(0).toInt());
            if(i == 0)
                root->addChild(p);
            else
                root->getChildren()[i]->addChild(p);
        }
        i++;
    }while(i < root->getChildren().size());
    user.setRootFolder(root);
}



QiFolder *QiDatabase::searchRootFolder(int id)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(
                "SELECT * FROM Folder "
                "WHERE ParentFolderID=:pid AND UserID=:uid"
                );
    sqlQuery.bindValue(":pid",0);
    sqlQuery.bindValue(":uid",id);
    sqlQuery.exec();
    if(!sqlQuery.isActive())
    {
        qDebug() << "hasUser prepare fails";
    }
    if(sqlQuery.next())
    {
        QiFolder *p = new QiFolder();
        p->setName(sqlQuery.value(1).toString());
        p->setParent(NULL);
        p->setType(QiObject::FOLDER);
        p->setID(sqlQuery.value(0).toInt());
        return p;
    }
    return NULL;
}

QSqlError QiDatabase::addUserSetting(const UserSetting& s)
{
    QSqlQuery sqlQuery;
    if(!sqlQuery.prepare(
                  "INSERT INTO Settings(AutoSignin,RemPassword) "
                  "VALUES(?,?,?);"))
    {
          return sqlQuery.lastError();
    }
    sqlQuery.addBindValue(s.isAutoSignin());
    sqlQuery.addBindValue(s.isRemPassword());
    sqlQuery.addBindValue(s.getUserID());
    sqlQuery.exec();
    if(!sqlQuery.isActive())
    {
        qDebug() << "hasUser prepare fails";
    }
    return QSqlError();
}


QSqlError QiDatabase::addDefaultUserSetting(int userid)
{
    UserSetting s;
    s.setAutoSign(false);
    s.setRemPassword(false);
    s.setUserID(userid);
    return addUserSetting(s);
}

QiDatabase* QiDatabase::getInstance()
{
    return uniqueQiDatabase;
}

bool QiDatabase::hasUser(const User &user)
{
    QSqlQuery sqlQuery;
    if(!sqlQuery.prepare(
                "SELECT COUNT(*) FROM User "
                "WHERE Email=?;"))
    {
        qDebug() << "hasUser prepare fails";
        return false;
    }
    sqlQuery.addBindValue(user.getUserName());
    sqlQuery.exec();
    if(!sqlQuery.isActive())
    {
        qDebug() << "hasUser prepare fails";
    }
    return sqlQuery.value(0).toInt();
}

int QiDatabase::getUserIDFormDB(User &user)
{
    QSqlQuery sqlQuery;
    if(!sqlQuery.prepare(
                "SELECT UserID FROM User "
                "WHERE Email=:Email;"))
    {
        qDebug() << "hasUser prepare fails";
        return 0;
    }
    sqlQuery.bindValue(":Email",user.getUserName());
    sqlQuery.exec();
    if(!sqlQuery.isActive())
    {
        qDebug() << "hasUser prepare fails";
    }
    return sqlQuery.value(0).toInt();
}

void QiDatabase::loadDataFromWeb()
{

}
