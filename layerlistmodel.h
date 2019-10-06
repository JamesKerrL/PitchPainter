#ifndef LAYERLISTMODEL_H
#define LAYERLISTMODEL_H

#include <QAbstractItemModel>
#include "layeritem.h"
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include "layermanager.h"
class layerlistmodel : public QAbstractItemModel
{
public:
    explicit layerlistmodel(layerManager *manager,QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::DropActions supportedDropActions() const override;
    bool insertRows(int position, int rows, const QModelIndex & parent) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
    layeritem *getItem(const QModelIndex &index) const;
    bool insertColumns(int position, int columns, const QModelIndex &parent) override;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;
    //Qt::DropActions supportedDragActions() const override;


    layerManager *getManager() const;
    void setManager(layerManager *manager);

private:
    layeritem *rootItem;
    layerManager *_manager;
public slots:
    void addLayer(layer *addedLayer,int position);
};

#endif // LAYERLISTMODEL_H
