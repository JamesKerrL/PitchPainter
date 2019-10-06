#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include "tool.h"
#include "pentool.h"
#include "circletool.h"
#include "brushtool.h"
#include <QTabletEvent>
class ToolManager
{
    static ToolManager * _toolManagerInstance;
public:
    ToolManager();
    ToolManager *getInstance();
    Tool *getActiveTool();
    void setActiveTool(QString ToolName);

    QColor getBorderColor() const;
    void setBorderColor(const QColor &value);

    QColor getFillColor() const;
    void setFillColor(const QColor &value);

    void setToolPressureSensitivity(bool sensitivityOn);
private:
    Tool *activeTool;
    QColor borderColor;
    QColor fillColor;
};

#endif // TOOLMANAGER_H
