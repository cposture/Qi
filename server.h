#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QList>
#include <QtNetwork/QTcpSocket>
class Server:public QObject
{
Q_OBJECT
public:
    static Server* uniqueServer;

    virtual ~Server(){}
    static Server* getInstance();
    void setAccessKey(const QString& ak);
    void setSecretKey(const QString& sk);
    QString getAccessKey() const;
    QString getSecretKey() const;
    bool signin();
    QStringList listAllFiles(QString bucketName);
    void doConnect();
private:
    QString accessKey;
    QString secretKey;

    Server();
    QTcpSocket *tcpSocket;
    int nextBlockSize;
    void connectToServer();
    void closeConnection();
    int sendRequest(QString command);
    QString makeCommand(const QStringList& cmdlist);
signals:
    void signin_signal();
public slots:
    bool sendSigninRequest();
private slots:
    QStringList receiveData();
    void socket_error(QAbstractSocket::SocketError e);
    void disconnected();
    void connected();
};

#endif // SERVER_H
