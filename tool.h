#ifndef TOOL_H
#define TOOL_H

#include <QString>
#include <QDebug>
#include <QPainter>
#include <QTabletEvent>
class Tool
{
public:
    Tool();
    virtual void mousePress(QPointF p,QPixmap &pixmap);
    virtual void mouseRelease(QPointF p,QPixmap &pixmap);
    //virtual void mouseMove(QPoint p,QImage &pixmap);
    virtual void mouseMove(QPointF p,QPixmap &pixmap);
    virtual void TabletMove(QTabletEvent *ev,QPixmap &pixmap,QPoint scenePos);
    virtual void TabletPress(QTabletEvent *ev,QPixmap &pixmap,QPoint scenePos);
    virtual void TabletRelease(QTabletEvent *ev,QPixmap &pixmap,QPoint scenePos);
    int getSize() const;
    void setSize(int value);

    int getOpacity() const;
    void setOpacity(int value);

    bool getSensitivityOn() const;
    void setSensitivityOn(bool value);

protected:
    QPointF lastpoint;
    int size = 10;
    int opacity = 1;
    bool sensitivityOn;
private:
    QString name;
};

#endif // TOOL_H
