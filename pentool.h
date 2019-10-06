#ifndef PENTOOL_H
#define PENTOOL_H

#include <QObject>
#include "tool.h"
#include <QPixmap>
#include <QPainter>
class pentool : public Tool
{
public:
    pentool();

    // Tool interface
public:
    void mousePress(QPointF p,QPixmap &pixmap) override;
    void mouseRelease(QPointF p,QPixmap &pixmap) override;
    void mouseMove(QPointF p,QPixmap &pixmap) override;

protected:
    void DrawLine(QPointF finish, QPixmap &pmap);
private:
    bool drawing =false;
};

#endif // PENTOOL_H
