#include "circletool.h"
#include "toolmanager.h"
circletool::circletool() : Tool()
{

}

void circletool::mousePress(QPointF p, QPixmap &pixmap)
{
    drawing = true;
    lastpoint = p;
}

void circletool::mouseRelease(QPointF p, QPixmap &pixmap)
{
    drawing = false;
}

void circletool::mouseMove(QPointF p, QPixmap &pixmap)
{
    if(!drawing)
        return;
    QPainter painter(&pixmap);
    QLineF line(lastpoint,p);
    int radius = line.length();
    painter.drawEllipse(QPointF(lastpoint), radius, radius);
}


