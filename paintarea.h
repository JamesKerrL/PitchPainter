#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
#include <QScrollArea>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "toolmanager.h"
#include <QTabletEvent>
class PaintArea : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PaintArea(QObject *parent = nullptr);
    //void paintEvent(QPaintEvent *event) override;
    void updateCursorSize(int value);
    void tabletMove(QTabletEvent *t,QPoint scenePos);
    void tabletPress(QTabletEvent *t,QPoint scenePos);
    void tabletRelease(QTabletEvent *t,QPoint scenePos);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev) override;

private:
    bool drawing = false;
    //int width = 800;
    //int height = 800;
    //QImage image = QPixmap(width, height).toImage();
    void drawLineTo(const QPoint &endPoint);
    QPoint lastPoint;
    ToolManager *toolmanager = toolmanager->getInstance();
    QPixmap *image;
    QGraphicsPixmapItem *m_item;
    bool tabletInUse = false;

signals:

public slots:
    void UpdateColor(const QColor &color);
    void draw();
};

#endif // PAINTAREA_H
