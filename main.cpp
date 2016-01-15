#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include "signindialog.h"
#include "user.h"
#include "qidatabase.h"
#include "server.h"

int mainCore(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int ret = mainCore(argc,argv);
    return ret;
}

int mainCore(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    SigninDialog signinDlg;
    User *user = User::getInstance();
    QiDatabase *dbMgr = QiDatabase::getInstance();
    Server *server = Server::getInstance();
    // db conncet
    QString db = "QMYSQL";
    QString hostName = "localhost";
    QString dbName = "SC";
    QString userName = "root";
    QString password = "";
    dbMgr->init(db,hostName,dbName,userName,password);
    // login
    signinDlg.show();
    signinDlg.exec();
    // load data from web
    //server->listAllFiles("notebook");
    dbMgr->loadDataFromWeb();
    // read db
    dbMgr->setUserRootFolder(*user);
    w.show();
    a.exec();
    return 0;
}
