#ifndef FOLDERTREEBASEMODEL_H
#define FOLDERTREEBASEbMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include "qifolder.h"

class FolderTreeBaseModel:public QAbstractItemModel
{
public:
    static const int columnNum = 1;

    FolderTreeBaseModel(QObject *parent = 0);
    ~FolderTreeBaseModel();

    void setRoot(QiFolder *root);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QiObject *at(const QModelIndex &index) const;
    QiFolder *rootFolder;
};

#endif // FOLDERTREEMODEL_H
