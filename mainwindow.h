#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QMouseEvent>
#include <QDebug>
#include "paintarea.h"
#include "colorwheel.h"
#include "scrollarea.h"
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include "layerstackwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void wheelEvent(QWheelEvent *event) override;
    int x1,y1;
    int y2;
    int x2 =-1;
    bool flip = false;
    bool firstpress = false;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
private:
    Ui::MainWindow *ui;
    PaintArea *paintArea;
    ColorWheel *colorwheel;
    ToolManager *toolmanager = toolmanager->getInstance();
    scrollarea *m_view;
    QLabel *sizeLabel;
    QLabel *opacityLabel;
    QSlider *sizeSlider;
    QSlider *opacitySlider;
    QPushButton *relativeSizetoPressureButton;
    bool pressureSensitivity = true;
    layerstackwidget *layerWidget;
    QDockWidget *layerDock;
protected:

private slots:
    void on_straightlineBut_clicked();
    void on_pushButton_2_clicked();
    void on_sizeSlider_valueChanged(int value);
    void on_opacitySlider_valueChanged(int value);
    void on_pressureSentivity_clicked();

    void on_brushToolButton_clicked();

public slots:
    void tabletMove(QTabletEvent *t,QPoint ScenePos);
    void tabletPress(QTabletEvent *t,QPoint ScenePos);
    void tabletRelease(QTabletEvent *t,QPoint ScenePos);
};


#endif // MAINWINDOW_H
