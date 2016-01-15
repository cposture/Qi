#include "signindialog.h"
#include "ui_signindialog.h"
#include "user.h"
#include <QDebug>
#include <QSqlError>
#include "setting.h"
#include "qidatabase.h"
#include "server.h"

SigninDialog::SigninDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SigninDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sign in now"));

    //spread window setting
    spread = false;
    spreadHeight = height()/3;

    ui->UserNamelineEdit->setPlaceholderText(tr("qiniu email"));
    ui->PasswordlineEdit->setPlaceholderText(tr(""));
    connect(ui->UserNamelineEdit,SIGNAL(textEdited(const QString &))
            ,this,SLOT(clearPrompt(const QString &)));
    connect(ui->PasswordlineEdit,SIGNAL(textEdited(const QString&))
            ,this,SLOT(clearPrompt(const QString&)));
}

SigninDialog::~SigninDialog()
{
    delete ui;
}

QString SigninDialog::getUserID() const
{
    return ui->UserNamelineEdit->text();
}

QString SigninDialog::getPassword() const
{
    return ui->PasswordlineEdit->text();
}

void  SigninDialog::prompt(const QString& str) const
{
    ui->Promptlabel->setText(QString("%1").arg("<font color=red>")
                             +str
                             +QString("%1").arg("</font>"));
}

void SigninDialog::clearPrompt(const QString &/*text*/) const
{
    prompt("");
}

void SigninDialog::on_SigninpushButton_clicked()
{
    User *user = User::getInstance();
    QiDatabase *dbMgr = QiDatabase::getInstance();

    // user login
    QString userID = getUserID();
    QString password = getPassword();
    qDebug() << "login user id: " << userID;
    qDebug() << "login user password" << password;
    if(userID.isEmpty() || password.isEmpty())
    {
        prompt("Username or password can not be empty.");
        return;
    }
    else
    {
        user->setUserName(userID);
        user->setPassword(password);
    }

    Server *server = Server::getInstance();
    // login qiniu
    server->doConnect();
    bool signin_state = server->signin();
    if(!signin_state)
    {
    }

    UserSetting setting;
    bool autosignin = (ui->AutocheckBox->checkState() != Qt::Unchecked);
    bool rempassword = (ui->RemcheckBox->checkState() != Qt::Unchecked);
    setting.setAutoSign(autosignin);
    setting.setRemPassword(rempassword);
    // new user
    if(!dbMgr->hasUser(*user))
    {
        int userid;
        dbMgr->addUser(*user);
        userid = dbMgr->getUserIDFormDB(*user);
        setting.setUserID(userid);
        dbMgr->addUserSetting(setting);
    }
    hide();
}

void SigninDialog::on_MorepushButton_clicked()
{
    if(!spread)
    {
        resize(width(),spreadHeight + height());
        spread = true;
    }
    else
    {
        resize(width(),height() - spreadHeight);
        spread = false;
    }
}
