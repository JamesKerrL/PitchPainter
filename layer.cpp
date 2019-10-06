#include "layer.h"

layer::layer(QString layerName)
{
    this->setName(layerName);
    int width = 200;
    int height = 200;
    image = new QPixmap(width, height);
}

layer::layer()
{

}


QPixmap *layer::getImage() const
{
    return image;
}

void layer::setImage(QPixmap *value)
{
    image = value;
}

bool layer::getIsVisible() const
{
    return isVisible;
}

void layer::setIsVisible(bool value)
{
    isVisible = value;
}

QString layer::getName() const
{
    return Name;
}

void layer::setName(const QString &value)
{
    Name = value;
}
