#include "layerlistmodel.h"

layerlistmodel::layerlistmodel(layerManager *manager,QObject *parent):QAbstractItemModel (parent)
{
    rootItem = new layeritem({tr("Title")});

    _manager = manager;
    connect(_manager,&layerManager::addLayer,this,&layerlistmodel::addLayer);
    layer newlayer("BackGround");
    manager->insertLayerAt(0,newlayer);
}

QVariant layerlistmodel::data(const QModelIndex &index, int role) const
{
    //qDebug() << "call to data" << index;
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
    {
        //qDebug() << "tick" <<index;
        return QVariant();
    }
    layeritem *item = static_cast<layeritem*>(index.internalPointer());
    //qDebug() << item->data(index.column())<<"f"<<index;
    return item->data(index.column());
}

QModelIndex layerlistmodel::index(int row, int column, const QModelIndex &parent) const
{
    //qDebug() << "call to index" << row << column;
    if (!hasIndex(row, column, parent))
            return QModelIndex();

        layeritem *parentItem;

        if (!parent.isValid())
            parentItem = rootItem;
        else
            parentItem = static_cast<layeritem*>(parent.internalPointer());
        layeritem *childItem = parentItem->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
        return QModelIndex();
}

Qt::ItemFlags layerlistmodel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable; //& (~Qt::ItemIsDropEnabled);
}

QVariant layerlistmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
            return rootItem->data(section);
        return QVariant();
}

QModelIndex layerlistmodel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

        layeritem *childItem = static_cast<layeritem*>(index.internalPointer());
        layeritem *parentItem = childItem->parentItem();

        if (parentItem == rootItem)
            return QModelIndex();

        return createIndex(parentItem->row(), 0, parentItem);
}

int layerlistmodel::rowCount(const QModelIndex &parent) const
{
    layeritem *parentItem;
        if (parent.column() > 0)
            return 0;
        if (!parent.isValid())
            parentItem = rootItem;
        else
            parentItem = static_cast<layeritem*>(parent.internalPointer());

        return parentItem->childCount();
}

int layerlistmodel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return static_cast<layeritem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

Qt::DropActions layerlistmodel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool layerlistmodel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if (rows < 1 || position < 0 || position > rowCount(parent))
            return false;
        beginInsertRows(QModelIndex(), position, position + rows - 1);
        for (int r = 0; r < rows; ++r)
            rootItem->insertChild(position,rows,rootItem->columnCount());
        endInsertRows();
        return true;
    //return QAbstractItemModel::insertRows(position,rows,parent);
}

bool layerlistmodel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    qDebug() << "move";
    QAbstractItemModel::moveRows(sourceParent,sourceRow,count,destinationParent,destinationChild);
    return true;
}

bool layerlistmodel::removeRows(int row, int count, const QModelIndex &parent)
{
    layeritem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    const bool success = parentItem->removeChildren(row, count);
    endRemoveRows();

    return success;
}

bool layerlistmodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //qDebug() << index;
    if (role != Qt::EditRole)
            return false;

    layeritem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result){
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole,Qt::DecorationRole});
    }

    return result;
}

layeritem *layerlistmodel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        layeritem *item = static_cast<layeritem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

bool layerlistmodel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool layerlistmodel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    //qDebug() << "setitem data" << index;
    //return QAbstractItemModel::setItemData(index,roles);
    if (roles.isEmpty())
            return false;
    if (std::any_of(roles.keyBegin(), roles.keyEnd(), [](int role) -> bool {
        return role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole;
    })) {

        return false;
    }
    auto roleIter = roles.constFind(Qt::EditRole);
    if (roleIter == roles.constEnd())
        roleIter = roles.constFind(Qt::DisplayRole);
    Q_ASSERT(roleIter != roles.constEnd());
    return setData(index, roleIter.value(), roleIter.key());
}

layerManager *layerlistmodel::getManager() const
{
    return _manager;
}

void layerlistmodel::setManager(layerManager *manager)
{
    _manager = manager;
}

void layerlistmodel::addLayer(layer *addedLayer, int position)
{
    qDebug() << addedLayer->getName();
    QMap<int, QVariant> map;
    map.insert(Qt::EditRole,addedLayer->getName());
    map.insert(Qt::DecorationRole,*addedLayer->getImage());
    qDebug() << "addLayer_in_model";
    insertRows(position,1,this->index(position,0,QModelIndex()));
    rootItem->setData(0,addedLayer->getName());
    rootItem->setData(1,*(addedLayer->getImage()));
    setItemData(this->index(position,0,QModelIndex()),map);

}
