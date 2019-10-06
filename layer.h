#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QPixmap>
class layer
{

public:
    layer(QString layerName);
    layer();
    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    bool getIsVisible() const;
    void setIsVisible(bool value);

    QString getName() const;
    void setName(const QString &value);
    QPixmap *image;
private:
    bool isVisible;
    QString Name;

signals:

public slots:
};

#endif // LAYER_H
