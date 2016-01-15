#ifndef FOLDERTREEMODEL_H
#define FOLDERTREEMODEL_H
#include "foldertreebasemodel.h"
#include "user.h"

class FolderTreeModel:public FolderTreeBaseModel
{
public:
    FolderTreeModel(QObject *parent = 0, User *u = 0);
    void update();
private:
    User *user;

};

#endif // FOLDERTREEMODEL_H
