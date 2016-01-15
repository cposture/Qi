#include "qiobject.h"

QiObject::QiObject()
{
}

QiObject::Type QiObject::getType() const
{
    return type;
}


QiObject *QiObject::getParent() const
{
    return parent;
}

QList<QiObject*> &QiObject::getChildren()
{
    return children;
}

const QString& QiObject::getName() const
{
    return name;
}

int QiObject::getID() const
{
    return id;
}

void QiObject::setName(const QString &n)
{
    name = n;
}

void QiObject::setParent(QiObject *p)
{
    parent = p;
}

void QiObject::setType(Type t)
{
    type = t;
}

void QiObject::setID(int i)
{
    id = i;
}

void QiObject::addChild(QiObject *child)
{
    if(child!=NULL)
        children.push_back(child);
}
