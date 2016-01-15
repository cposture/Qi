#ifndef QIFOLDER_H
#define QIFOLDER_H

#include "qiobject.h"
#include <QMap>

class QiFolder:public QiObject
{
public:
    QiFolder();
    QiObject* getChild(const QString& name) const;
    bool isRoot() const;
private:
    bool isroot;
};

#endif // QIFOLDER_H
