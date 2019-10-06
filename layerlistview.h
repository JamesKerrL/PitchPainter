#ifndef LAYERLISTVIEW_H
#define LAYERLISTVIEW_H

#include <QListView>
#include <QDebug>
#include "layerlistmodel.h"
class LayerListView : public QListView
{
public:
    LayerListView(QWidget *parent = nullptr);

signals:
    void clicked(const QModelIndex &index);

public slots:
    void clickedSlot(const QModelIndex &index);
    void currentChanged(const QModelIndex & current, const QModelIndex & previous) override;
};

#endif // LAYERLISTVIEW_H
