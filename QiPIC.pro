#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T01:53:09
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QiPIC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    foldertreeview.cpp \
    qiobject.cpp \
    qifolder.cpp \
    qifile.cpp \
    qidatabase.cpp \
    foldertreebasemodel.cpp \
    foldertreemodel.cpp \
    user.cpp \
    server.cpp \
    setting.cpp \
    signindialog.cpp



HEADERS  += mainwindow.h \
    foldertreeview.h \
    qiobject.h \
    qifolder.h \
    qifile.h \
    qidatabase.h \
    foldertreebasemodel.h \
    foldertreemodel.h \
    user.h \
    server.h \
    setting.h \
    signindialog.h



UI_DIR = ./UI
FORMS    += mainwindow.ui \
    signindialog.ui
INCLUDEPATH += /usr/include
LIBS += -L/usr/lib -lssl
DISTFILES +=

RESOURCES += \
    resources.qrc
