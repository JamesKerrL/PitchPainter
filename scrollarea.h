#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QDebug>
#include <QTabletEvent>
#include "toolmanager.h"
class scrollarea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit scrollarea(QWidget *parent = nullptr);

    QPixmap getCursorimage() const;
    void setCursorimage(const QPixmap &value);

protected:
    virtual void wheelEvent(QWheelEvent * event);
    bool viewportEvent(QEvent *event);
    ToolManager *m = m->getInstance();
    QPointF tabletEventPos(const QEvent *event);
    void enterEvent(QEvent *event);
    void showEvent(QShowEvent *event);
    QPixmap cursorimage;
signals:
    void tabletPenMove(QTabletEvent *t,QPoint scenePos);
    void tabletPress(QTabletEvent *t,QPoint scenePos);
    void tabletRelease(QTabletEvent *t,QPoint scenePos);
public slots:
    //bool event(QEvent *event);

};

#endif // SCROLLAREA_H
