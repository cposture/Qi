#include "foldertreemodel.h"

FolderTreeModel::FolderTreeModel(QObject *parent, User *u):FolderTreeBaseModel(parent),user(u)
{
    update();
}

void FolderTreeModel::update()
{
    //setRoot(user->getRootFolder());
}

