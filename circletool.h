#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "tool.h"

class circletool : public Tool
{
public:
    circletool();

public:
    void mousePress(QPointF p,QPixmap &pixmap) override;
    void mouseRelease(QPointF p,QPixmap &pixmap) override;
    void mouseMove(QPointF p,QPixmap &pixmap) override;
protected:
    void DrawCircle(QPoint finish, QPixmap &pmap);
private:
    bool drawing =false;
    QPointF currentPoint;
};

#endif // CIRCLETOOL_H
