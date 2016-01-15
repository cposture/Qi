#ifndef QIOBJECT_H
#define QIOBJECT_H

#include <QDateTime>
#include <QString>
#include <QMap>

class QiObject
{
public:
    enum Type{
        FOLDER,
        FILE
    };
    typedef unsigned int FileSize;

public:
    QiObject();
    Type getType() const;
    QiObject *getParent() const;
    QList<QiObject *> &getChildren();
    const QString& getName() const;
    int getID()const;
    void setName(const QString& n);
    void setType(Type t);
    void setParent(QiObject *p);
    void setID(int i);
    void addChild(QiObject *child);
private:
    QString name;
    Type type;
    QiObject *parent;
    QList<QiObject*> children;
    int id;
};

#endif // QIOBJECT_H
