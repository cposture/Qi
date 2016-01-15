#ifndef QIFILE_H
#define QIFILE_H

#include "qiobject.h"
class QiFile:public QiObject
{
public:
    QiFile();
    QDateTime getUploadtime() const;
    FileSize getSize() const;
private:
    FileSize size;
    QDateTime uploadTime;
};

#endif // QIFILE_H
