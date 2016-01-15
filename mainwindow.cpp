#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signindialog.h"
#include "user.h"
//#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    //move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
