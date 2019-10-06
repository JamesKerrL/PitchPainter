#include "layeritem.h"

layeritem::layeritem(const QVector<QVariant> &data, layeritem *parent)
    : m_itemData(data), m_parentItem(parent)
{

}

void layeritem::appendChild(layeritem *child)
{
    m_childItems.append(child);
}

bool layeritem::insertChild(int position,int count, int columns)
{
    if (position < 0 || position > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        layeritem *item = new layeritem(data, this);
        m_childItems.insert(position, item);
    }

    return true;
}

bool layeritem::move(int row, layeritem *toChild)
{
    return true;
}

bool layeritem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_itemData.size())
            return false;

    m_itemData[column] = value;
    return true;
}

bool layeritem::insertColumns(int position, int columns)
{
    if (position < 0 || position > m_itemData.size())
            return false;

        for (int column = 0; column < columns; ++column)
            m_itemData.insert(position, QVariant());

        for (layeritem *child : qAsConst(m_childItems))
            child->insertColumns(position, columns);

        return true;
}

bool layeritem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size())
            return false;

        for (int row = 0; row < count; ++row)
            delete m_childItems.takeAt(position);

        return true;
}

layeritem *layeritem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int layeritem::childCount() const
{
    return m_childItems.count();
}

int layeritem::columnCount() const
{
    return m_itemData.count();
}

QVariant layeritem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
            return QVariant();
        return m_itemData.at(column);
}

int layeritem::row() const
{
    if (m_parentItem)
            return m_parentItem->m_childItems.indexOf(const_cast<layeritem*>(this));
    return 0;
}

layeritem *layeritem::parentItem()
{
    return m_parentItem;
}
