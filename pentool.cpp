#include "pentool.h"
#include "toolmanager.h"
pentool::pentool() : Tool()
{

}

void pentool::mousePress(QPointF p,QPixmap &pixmap)
{
    qDebug()<<"mousePress";
    drawing = true;
    lastpoint = p;
}

void pentool::mouseRelease(QPointF p,QPixmap &pixmap)
{
    drawing = false;
}

void pentool::mouseMove(QPointF p,QPixmap &pixmap)
{
    DrawLine(p,pixmap);
}

void pentool::DrawLine( QPointF finish, QPixmap &pmap)
{
    if(!drawing)
        return;
    QPainter painter(&pmap);
    ToolManager *tool = tool->getInstance();
    painter.setPen(tool->getBorderColor());
    painter.drawLine(lastpoint, finish);
    lastpoint = finish;
}
