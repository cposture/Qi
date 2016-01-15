#include "server.h"
#include <QDebug>
#include <QProcess>
#include <QFileInfo>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QHostAddress>
#include "user.h"

Server* Server::uniqueServer = new Server();
Server::Server()
{
    //question:when socket connects here,the data can not be send,why?
}

void Server::doConnect()
{
    tcpSocket = new QTcpSocket(this);
    QObject::connect(tcpSocket, SIGNAL(connected()),this, SLOT(connected()));
    QObject::connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
    QObject::connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(socket_error(QAbstractSocket::SocketError)));
    QObject::connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    QObject::connect(this,SIGNAL(signin_signal()),this,SLOT(sendSigninRequest()),Qt::QueuedConnection);
    connectToServer();
}

void Server::connectToServer()
{
    tcpSocket->connectToHost("127.0.0.1",8888);
    nextBlockSize = 0;

}
void Server::closeConnection()
{
    tcpSocket->close();
}
void Server::connected()
{
    qDebug() << "connected...";
}

void Server::socket_error(QAbstractSocket::SocketError e)
{
    qDebug() << "socket error...";
}

void Server::disconnected()
{
    qDebug() << "disconncted...";
}

Server* Server::getInstance()
{
    return uniqueServer;
}

QString Server::getAccessKey()const
{
    return accessKey;
}

QString Server::getSecretKey()const
{
    return secretKey;
}

void Server::setAccessKey(const QString &ak)
{
    accessKey = ak;
}

void Server::setSecretKey(const QString &sk)
{
    secretKey = sk;
}

bool Server::signin()
{
    QProcess proc;
    QStringList argv;
    QString filepath;
    // login qiniu server
    // Linux or Windows
    if(QFileInfo::exists("./qrsctl"))
    {
        filepath = "./qrsctl";
    }
    else if(QFileInfo::exists("./qrsctl.exe"))
    {
        filepath = "./qrsctl.exe";
    }
    else
    {
        QMessageBox::critical(0,"Error","There has no qrsctl");
        return false;
    }

    User *user = User::getInstance();
    argv << "login" << user->getUserName() << user->getPassword();
    int state = proc.execute(filepath,argv);

    if(state == -2)
    {
        QMessageBox::critical(0,"Error","There has no qrsctl program");
        return false;
    }
    else if(state == -1)
    {
        QMessageBox::critical(0,"Error","qrsctl program is crashed.");
        return false;
    }
    qDebug() << "SigninDialog::on_SigninpushButton_clicked:sign in succeed";

    // gets accessky and secretkey
    QByteArray result;
    argv.clear();
    argv << "appinfo";
    proc.start(filepath,argv,QIODevice::ReadWrite);
    proc.waitForFinished();
    result = proc.readAllStandardOutput();

    if(result == QString("%1").arg("AppInfo failed: bad token\n"))
    {
        return false;
    }

    QRegularExpression re = QRegularExpression("AccessKey: (.*?)\\s\\nSecretKey: (.*?)\\s\\n");
    QRegularExpressionMatch  rx =re.match(result);
    QStringList slist = rx.capturedTexts();
    QString ak = slist[1];
    QString sk = slist[2];
    // set server's access and secret key
    setAccessKey(ak);
    setSecretKey(sk);
    // send signin request to our server
    emit signin_signal();
    //sendSigninRequest();
    return true;
}

bool Server::sendSigninRequest()
{
    QStringList cmdlist;
    QString		request;
    User *user = User::getInstance();

    cmdlist << "login" << accessKey << secretKey << user-> getUserName();
    request = makeCommand(cmdlist);
    return sendRequest(request);
}
QString Server::makeCommand(const QStringList& cmdlist)
{
    QString command = "";
    int commandNum;

    commandNum = cmdlist.size();
    if(commandNum == 0)
        return QString();

    command = command
            + "*"
            +  QString("%1").arg(commandNum)
            + "\r\n";
    for(int i = 0; i < commandNum; i++)
    {
        command = command
                + "$"
                + QString("%1").arg(cmdlist[i].size())
                + "\r\n"
                + cmdlist[i]
                + "\r\n";
    }
    return command;
}

QStringList Server::listAllFiles(QString bucketName)
{
    //send request
    User *user = User::getInstance();
    QString command;
    command = command
            + "*3\r\n"
            + "$8\r\n"
            + "list_all\r\n"
            + "$" + QString("%1").arg(user->getUserName().size()) + "\r\n"
            + user->getUserName() + "\r\n"
            + "$" + QString("%1").arg(bucketName.size()) + "\r\n"
            + bucketName + "\r\n";
    sendRequest(command);
    return QStringList();
}


int Server::sendRequest(QString command)
{
    QByteArray block;
    block.append(command);
    int sendNum = 0;
    int size = block.size();
    sendNum = tcpSocket->write(block);
    return sendNum;
}

QStringList Server::receiveData()
{
    qDebug() << "reading...";
    QStringList list;
    qDebug() << tcpSocket->readAll();
    /*
    QDataStream in(tcpSocket);
    char *s;
    unsigned int size;
    QStringList slist;
    forever{
        if(nextBlockSize == 0)
        {
            if(tcpSocket->bytesAvailable() < 4)
                continue;
            else
                in >> nextBlockSize;
        }
        if(tcpSocket->bytesAvailable() < nextBlockSize)
            continue;
        in.readBytes(s,size);
        break;
    }
    QString si = QString("%1").arg(s);
    slist = si.split("\\r\\n");
    return slist;
    */

}
