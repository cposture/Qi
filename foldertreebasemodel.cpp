#include "foldertreebasemodel.h"
#include "qiobject.h"

FolderTreeBaseModel::FolderTreeBaseModel(QObject *parent):QAbstractItemModel(parent)
{
}
FolderTreeBaseModel::~FolderTreeBaseModel()
{
    delete rootFolder;
}

void FolderTreeBaseModel::setRoot(QiFolder *root)
{
    beginResetModel();
    delete rootFolder;
    rootFolder = root;
    endResetModel();
}


QModelIndex FolderTreeBaseModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid() || NULL == rootFolder || row < 0 || column < 0)
        return QModelIndex();

    QiObject *parentObject = at(parent);

    if(NULL == parentObject || parentObject->getChildren().size() < row)
        return QModelIndex();

    QiObject *children = parentObject->getChildren()[row];
    if(NULL == children)
        return QModelIndex();
    else if(children->getType() != QiObject::FOLDER)
        return createIndex(row,column,children);
    else if(children->getChildren().size() < column)
        return QModelIndex();
    else
        return createIndex(row,column,children->getChildren()[column]);
}

QiObject* FolderTreeBaseModel::at(const QModelIndex &index) const
{
    if(!index.isValid())
        return rootFolder;
    return static_cast<QiObject*>(index.internalPointer());
}

QModelIndex FolderTreeBaseModel::parent(const QModelIndex &child) const
{
    QiObject *chileNode = at(child);
    if(!child.isValid() || NULL == chileNode)
        return QModelIndex();
    QiObject *parentNode = chileNode->getParent();
    if(NULL == parentNode)
        return QModelIndex();
    QiObject *grandparentNode = parentNode->getParent();
    if(NULL == grandparentNode)
        return QModelIndex();

    if(grandparentNode->getChildren().size() >= child.row())
    {
        int row = grandparentNode->getChildren().indexOf(parentNode);
        return createIndex(row,0,parentNode);
    }
    else
    {
        return QModelIndex();
    }
}

int FolderTreeBaseModel::columnCount(const QModelIndex &/*parent*/) const
{
    return columnNum;
}

int FolderTreeBaseModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
        return 0;
    QiObject *parentNode = at(parent);
    if(NULL != parentNode)
        return parentNode->getChildren().size();
    else
        return 0;
}

QVariant FolderTreeBaseModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    QiObject *node = at(index);
    if(NULL == node)
        return QVariant();
    else
        return QVariant(node->getName());
}
