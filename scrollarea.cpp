#include "scrollarea.h"

scrollarea::scrollarea(QWidget *parent) : QGraphicsView(parent)
{
    viewport()->setMouseTracking(true);
}

void scrollarea::wheelEvent(QWheelEvent *event)
{
    qDebug() << "atempt to scroll";
}

bool scrollarea::viewportEvent(QEvent *event)
{
    //if(_disabletablet)
        //return QGraphicsView::viewportEvent(event);
    QTabletEvent *tabletEvent;
    if(event->type() == QEvent::TabletMove) {
        event->accept();
        tabletEvent = static_cast<QTabletEvent *>(event);

        emit this->tabletPenMove(tabletEvent,this->mapToScene(tabletEvent->pos()).toPoint() );

    } else if(event->type() == QEvent::TabletPress) {
        event->accept();
        tabletEvent = static_cast<QTabletEvent *>(event);
        emit this->tabletPress(tabletEvent,this->mapToScene(tabletEvent->pos()).toPoint());

    } else if(event->type() == QEvent::TabletRelease) {
        event->accept();
        tabletEvent = static_cast<QTabletEvent *>(event);
        emit this->tabletRelease(tabletEvent,this->mapToScene(tabletEvent->pos()).toPoint());
    } else {
        return QGraphicsView::viewportEvent(event);
    }

    return true;
}

void scrollarea::enterEvent(QEvent *event)
{
    ToolManager *t = t->getInstance();
    QGraphicsView::enterEvent(event);
    int width = t->getActiveTool()->getSize();
    int height = t->getActiveTool()->getSize();
    QPixmap cursorimage = QPixmap(width*2, height*2);
    cursorimage.fill(QColor(0,0,0,0));
    QPainter painter(&cursorimage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.drawEllipse(QPoint(width,height),t->getActiveTool()->getSize(),t->getActiveTool()->getSize());
    viewport()->setCursor(cursorimage);
}

void scrollarea::showEvent(QShowEvent *event)
{

}

QPixmap scrollarea::getCursorimage() const
{
    return cursorimage;
}

void scrollarea::setCursorimage(const QPixmap &value)
{
    cursorimage = value;
}
QPointF tabletEventPos(const QEvent *event)
{
    const QTabletEvent *e = static_cast<const QTabletEvent*>(event);
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    return e->pos() + QPointF(0.5, 0.5);
#else
    return e->posF();
#endif
}
