#include "brushtool.h"
#include "toolmanager.h"
brushtool::brushtool() : Tool()
{

}

void brushtool::mousePress(QPointF p, QPixmap &pixmap)
{
    //drawing = true;
    //lastpoint = p;
}

void brushtool::mouseRelease(QPointF p, QPixmap &pixmap)
{
    //drawing = false;
}

void brushtool::mouseMove(QPointF p, QPixmap &pixmap)
{
    //drawStamp(p,pixmap);
}

void brushtool::drawStamp(QPointF p, QPixmap &pixmap)
{
    if(!drawing)
        return;
    QPainter painter(&pixmap);
    float deltaX = p.x() - lastpoint.x();
    float deltaY = p.y() - lastpoint.y();

    float distance = sqrt( deltaX * deltaX + deltaY * deltaY );
    float stepX = 0.0;
    float stepY = 0.0;
    if (distance > 0.0) {
        float invertDistance = 1.0 / distance;
        stepX = deltaX * invertDistance;
        stepY = deltaY * invertDistance;
    }

    ToolManager *tool = tool->getInstance();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QBrush my_brush;
    //qDebug()<<opacity;
    QColor color = QColor(tool->getFillColor().red(),tool->getFillColor().green(),tool->getFillColor().blue(),opacity);
    painter.setBrush(color);
    painter.setPen(color);
    float spacing = 0.9;
    float addX =stepX;
    float addY = stepY;
    while ( distance >= spacing ) {
        // ... increment the offset and stamp...

        // Remove the distance we just covered
        distance -= spacing;
        painter.drawEllipse(QPoint(lastpoint.x()+addX,lastpoint.y()+addY),(int)(size),(int)(size));
        addX +=stepX;
        addY += stepY;
    }
    lastpoint = p;
}

void brushtool::TabletMove(QTabletEvent *t, QPixmap &pixmap,QPoint scenePos)
{

    if(!drawing || scenePos.x() <0||scenePos.y()<0)
        return;
    QPainter painter(&pixmap);

    float deltaX = scenePos.x() - lastpoint.x();
    float deltaY = scenePos.y() - lastpoint.y();

    float distance = sqrt( deltaX * deltaX + deltaY * deltaY );
    float stepX = 0.0;
    float stepY = 0.0;
    if (distance > 0.0) {
        float invertDistance = 1.0 / distance;
        stepX = deltaX * invertDistance;
        stepY = deltaY * invertDistance;
    }

    ToolManager *tool = tool->getInstance();
    //painter.setRenderHint(QPainter::Antialiasing);
    //painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QBrush my_brush;

    QColor color = QColor(tool->getFillColor().red(),tool->getFillColor().green(),tool->getFillColor().blue(),opacity);
    painter.setBrush(color);
    painter.setPen(color);
    float spacing = 1;
    float addX =stepX;
    float addY = stepY;
    while ( distance >= spacing ) {
        // ... increment the offset and stamp...

        // Remove the distance we just covered
        distance -= spacing;
        if(sensitivityOn)
            painter.drawEllipse(QPoint(lastpoint.x()+addX,lastpoint.y()+addY),(int)(size*t->pressure()),(int)(size*t->pressure()));
        else
            painter.drawEllipse(QPoint(lastpoint.x()+addX,lastpoint.y()+addY),(int)(size),(int)(size));
        addX +=stepX;
        addY += stepY;
    }
    lastpoint = scenePos;
}

void brushtool::TabletPress(QTabletEvent *t, QPixmap &pixmap,QPoint scenePos)
{
    drawing = true;
    lastpoint = scenePos;
}

void brushtool::TabletRelease(QTabletEvent *t, QPixmap &pixmap,QPoint scenePos)
{
    drawing = false;
}

