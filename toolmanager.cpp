#include "toolmanager.h"
ToolManager * ToolManager::_toolManagerInstance;
ToolManager::ToolManager()
{
    activeTool = new pentool();
}

ToolManager *ToolManager::getInstance()
{
    if(_toolManagerInstance == NULL)
    {
        _toolManagerInstance = new ToolManager();
    }
    return _toolManagerInstance;
}

Tool* ToolManager::getActiveTool()
{
    return activeTool;
}

void ToolManager::setActiveTool(QString ToolName)
{
    int size = activeTool->getSize();
    int opacity = activeTool->getOpacity();
    if(QString::compare(ToolName, "linetool", Qt::CaseInsensitive)==0){
        qDebug() << "ActiveTool Set to Pen";
        delete activeTool;
        activeTool = new pentool();
        activeTool->setSize(size);
        activeTool->setOpacity(opacity);
    }
    else if(QString::compare(ToolName, "circle", Qt::CaseInsensitive)==0){
        delete activeTool;
        activeTool = new circletool();
        qDebug() << "ActiveTool Set to Circle";
        activeTool->setSize(size);
        activeTool->setOpacity(opacity);
    }
    else if(QString::compare(ToolName, "brush", Qt::CaseInsensitive)==0){
        delete activeTool;
        activeTool = new brushtool();
        qDebug() << "ActiveTool Set to Brush";
        activeTool->setSize(size);
        activeTool->setOpacity(opacity);
    }
    else{
        qDebug() << "Unknown Tool";
    }
}

QColor ToolManager::getBorderColor() const
{
    return borderColor;
}

void ToolManager::setBorderColor(const QColor &value)
{
    borderColor = value;
}

QColor ToolManager::getFillColor() const
{
    return fillColor;
}

void ToolManager::setFillColor(const QColor &value)
{
    fillColor = value;
}

void ToolManager::setToolPressureSensitivity(bool sensitivityOn)
{
    activeTool->setSensitivityOn(sensitivityOn);
}



