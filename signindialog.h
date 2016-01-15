#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>

namespace Ui {
class SigninDialog;
}

class SigninDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SigninDialog(QWidget *parent = 0);
    ~SigninDialog();
    QString getUserID() const;
    QString getPassword() const;
    void prompt(const QString& str) const;

private:
    Ui::SigninDialog *ui;
    bool spread;
    int spreadHeight;

public slots:
    void clearPrompt(const QString &text) const;
private slots:
    void on_SigninpushButton_clicked();
    void on_MorepushButton_clicked();
};

#endif // SIGNINDIALOG_H
