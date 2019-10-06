#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <QVariant>
#include <QVector>
#include <QDebug>
class layeritem
{
public:
    explicit layeritem(const QVector<QVariant> &data, layeritem *parentItem = nullptr);
    void appendChild(layeritem *child);
    bool insertChild(int position, int count, int columns);

    bool move(int row, layeritem *toChild);
    bool setData(int column, const QVariant &value);
    bool insertColumns(int position, int columns);

    bool removeChildren(int position, int count);

    layeritem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    layeritem *parentItem();
private:
    QVector<layeritem*> m_childItems;
    QVector<QVariant> m_itemData;
    layeritem *m_parentItem;
};
#endif // LAYERITEM_H
