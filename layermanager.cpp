#include "layermanager.h"


layerManager::layerManager(QObject *parent):QObject(parent)
{
}

void layerManager::insertLayerAt(int position, layer &insertLayer)
{
    layers.insert(position,insertLayer);
    emit addLayer(&insertLayer,position);
}

void layerManager::removeLayerAt(int position)
{
    layers.remove(position);
}

QVector<layer> layerManager::getLayers() const
{
    return layers;
}

void layerManager::setLayers(const QVector<layer> &value)
{
    layers = value;
}

layer *layerManager::getActiveLayer() const
{
    return activeLayer;
}

void layerManager::setActiveLayer(layer *value)
{
    activeLayer = value;
}

QString layerManager::getDefaultName()
{
    QString name = "default_";
    name.append(QString::number(layers.length()-1));
    return name;
}

void layerManager::addLayerClicked()
{
    layer newlayer(getDefaultName());
    insertLayerAt(0,newlayer);
}
