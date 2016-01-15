#include "qifile.h"

QiFile::QiFile()
{

}

QiObject::FileSize QiFile::getSize() const
{
    return size;
}

QDateTime QiFile::getUploadtime() const
{
    return uploadTime;
}
