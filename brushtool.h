#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include "tool.h"
class brushtool : public Tool
{
public:
    brushtool();
    void mousePress(QPointF p,QPixmap &pixmap) override;
    void mouseRelease(QPointF p,QPixmap &pixmap) override;
    void mouseMove(QPointF p,QPixmap &pixmap) override;
    void drawStamp(QPointF p,QPixmap &pixmap);
    void TabletMove(QTabletEvent *t,QPixmap &pixmap,QPoint scenePos) override;
    void TabletPress(QTabletEvent *t,QPixmap &pixmap,QPoint scenePos) override;
    void TabletRelease(QTabletEvent *t,QPixmap &pixmap,QPoint scenePos) override;

private:
    bool drawing =false;
};

#endif // BRUSHTOOL_H
