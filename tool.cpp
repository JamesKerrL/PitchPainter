#include "tool.h"

Tool::Tool()
{

}

void Tool::mousePress(QPointF p, QPixmap &pixmap)
{

}

void Tool::mouseRelease(QPointF p, QPixmap &pixmap)
{

}

void Tool::mouseMove(QPointF p, QPixmap &pixmap)
{

}

void Tool::TabletMove(QTabletEvent *ev, QPixmap &pixmap,QPoint scenePos)
{

}

void Tool::TabletPress(QTabletEvent *ev, QPixmap &pixmap,QPoint scenePos)
{

}

void Tool::TabletRelease(QTabletEvent *ev, QPixmap &pixmap,QPoint scenePos)
{

}


int Tool::getSize() const
{
    return size;
}

void Tool::setSize(int value)
{
    size = value;
}

int Tool::getOpacity() const
{
    return opacity;
}

void Tool::setOpacity(int value)
{
    opacity = value;
}

bool Tool::getSensitivityOn() const
{
    return sensitivityOn;
}

void Tool::setSensitivityOn(bool value)
{
    sensitivityOn = value;
}

