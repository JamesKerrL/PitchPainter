#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QVector>
#include "layer.h"
#include <QObject>

class layerManager:public QObject
{
    Q_OBJECT
public:
    explicit layerManager(QObject * parent=0);

    void insertLayerAt(int position,layer &insertLayer);
    void removeLayerAt(int position);
    QVector<layer> getLayers() const;
    void setLayers(const QVector<layer> &value);

    layer *getActiveLayer() const;
    void setActiveLayer(layer *value);

private:
    QVector<layer> layers;
    layer *activeLayer;
    QString getDefaultName();
signals:
    void addLayer(layer *addedLayer,int position);
    void removeLayer(int position);
public slots:
    void addLayerClicked();
};
#endif // LAYERMANAGER_H
