#include "paintarea.h"

PaintArea::PaintArea(QObject *parent) : QGraphicsScene(parent)
{
    //this->setMouseTracking(true);
    //scrollArea->setVisible(true);
    image = new QPixmap(3000, 2000);
    image->fill(Qt::white);
    m_item = addPixmap(*image);
    m_item->setTransformationMode(Qt::SmoothTransformation);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(draw()));
    timer->start(30);

}

void PaintArea::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    if(tabletInUse)
        ev->ignore();
    toolmanager->getActiveTool()->mouseMove(ev->scenePos(),*image);
}

void PaintArea::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    if(tabletInUse)
        ev->ignore();
    toolmanager->getActiveTool()->mousePress(ev->scenePos(),*image);
}

void PaintArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if(tabletInUse)
        ev->ignore();
    toolmanager->getActiveTool()->mouseRelease(ev->scenePos(),*image);
}



void PaintArea::draw()
{
    m_item->setPixmap(*image);
}

void PaintArea::UpdateColor(const QColor &color)
{
    toolmanager->setBorderColor(color);
    toolmanager->setFillColor(color);
    qDebug() << "ColorChange";
}


void PaintArea::updateCursorSize(int value)
{

    int width = value;
    int height = value;
    QPixmap cursorimage = QPixmap(width, height);
    cursorimage.fill(QColor(0,0,0,0));
    QPainter painter(&cursorimage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(Qt::black);
    painter.drawLine(QPoint(0,0),QPoint(value,value));
    //this->setCursor(QCursor(cursorimage));
}

void PaintArea::tabletMove(QTabletEvent *t,QPoint scenePos)
{
    toolmanager->getActiveTool()->TabletMove(t,*image,scenePos);

}

void PaintArea::tabletPress(QTabletEvent *t,QPoint scenePos)
{
    tabletInUse = true;
    //qDebug() << "sec" << scenePos;
    toolmanager->getActiveTool()->TabletPress(t,*image,scenePos);

}

void PaintArea::tabletRelease(QTabletEvent *t,QPoint scenePos)
{
    tabletInUse = false;
    toolmanager->getActiveTool()->TabletRelease(t,*image,scenePos);
}
