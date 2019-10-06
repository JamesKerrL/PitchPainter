#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <Qt>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //declerations
    paintArea = new PaintArea;
    colorwheel = new ColorWheel;
    m_view = new scrollarea();
    setWindowTitle(tr("Scribble"));
    sizeLabel = new QLabel();
    opacityLabel = new QLabel();
    sizeSlider = new QSlider();
    opacitySlider = new QSlider();
    relativeSizetoPressureButton = new QPushButton();
    layerWidget = new layerstackwidget();
    layerDock = new QDockWidget();
    ui->setupUi(this);

    //setup canvas
    ui->cenlayout->addWidget(m_view);
    m_view->setScene(paintArea);
    m_view->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));

    //setup toolbar
    colorwheel->setMinimumSize(QSize(200,300));
    colorwheel->setMaximumSize(QSize(300,500));
    ui->cwheel->addWidget(colorwheel);


    //ui settings
    ui->mainToolBar->addWidget(sizeLabel);
    ui->mainToolBar->addWidget(sizeSlider);
    ui->mainToolBar->addWidget(relativeSizetoPressureButton);
    ui->mainToolBar->addWidget(opacityLabel);
    ui->mainToolBar->addWidget(opacitySlider);


    sizeSlider->setOrientation(Qt::Horizontal);
    opacitySlider->setOrientation(Qt::Horizontal);
    sizeSlider->setValue(10);
    opacitySlider->setValue(99);
    sizeLabel->setText("Size "+QString::number(00).rightJustified(2, '0'));
    opacityLabel->setText("Opacity "+QString::number(00).rightJustified(2, '0'));
    layerDock->setWidget(layerWidget);
    ui->dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    ui->dockWidget_2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::TopLeftCorner,Qt::TopDockWidgetArea);
    ui->dockWidget_2->setMinimumSize(QSize(colorwheel->minimumSize().width()+10,colorwheel->minimumSize().height()));
    this->splitDockWidget(ui->dockWidget_2,layerDock,Qt::Vertical);

    //connects
    QObject::connect(colorwheel,SIGNAL(colorChange(const QColor)),paintArea,SLOT(UpdateColor(const QColor)));
    QObject::connect(sizeSlider,SIGNAL(valueChanged(int)),this,SLOT(on_sizeSlider_valueChanged(int)));
    QObject::connect(opacitySlider,SIGNAL(valueChanged(int)),this,SLOT(on_opacitySlider_valueChanged(int)));
    QObject::connect(m_view,&scrollarea::tabletPenMove,this,&MainWindow::tabletMove);
    QObject::connect(m_view,&scrollarea::tabletPress,this,&MainWindow::tabletPress);
    QObject::connect(m_view,&scrollarea::tabletRelease,this,&MainWindow::tabletRelease);
    QObject::connect(relativeSizetoPressureButton,&QPushButton::clicked,this,&MainWindow::on_pressureSentivity_clicked);

    //setup
    toolmanager->setFillColor(colorwheel->color());
    toolmanager->setBorderColor(colorwheel->color());
    toolmanager->getActiveTool()->setSize(10);
    toolmanager->getActiveTool()->setOpacity(99);
    paintArea->updateCursorSize(10);
    this->showMaximized();

    //images
    QPixmap pixmap("D:/Documents/pitch/svgs/paintbrush.svg");
    QIcon ButtonIcon(pixmap);
    ui->brushToolButton->setIcon(ButtonIcon);
    ui->brushToolButton->setIconSize(QSize(77,25));
    ui->brushToolButton->setFixedSize(QSize(77,25));

    //Style Sheet
    QFile File("D:/Documents/pitch/sheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    qreal delta = 1 + (event->delta() > 0 ? 0.1 : -0.1);
    m_view->scale(delta, delta);
}


void MainWindow::on_straightlineBut_clicked()
{
    qDebug() << "selected Line tool";
    toolmanager->setActiveTool("linetool");
}

void MainWindow::on_pushButton_2_clicked()
{
    toolmanager->setActiveTool("circle");
}
void MainWindow::on_sizeSlider_valueChanged(int value)
{
    if(value<1)
        value = 1;
    toolmanager->getActiveTool()->setSize(value);
    sizeLabel->setText("Size "+QString::number(value).rightJustified(2, '0'));
    paintArea->updateCursorSize(value);
}

void MainWindow::on_opacitySlider_valueChanged(int value)
{
    if(value<1)
        value = 1;
    toolmanager->getActiveTool()->setOpacity(value);
    opacityLabel->setText("Opacity "+QString::number(value).rightJustified(2, '0'));
}

void MainWindow::on_pressureSentivity_clicked()
{
    if(pressureSensitivity)
    {
        pressureSensitivity = false;
        toolmanager->setToolPressureSensitivity(false);
        qDebug() << "sensitivity on";
    }
    else
    {
        pressureSensitivity = true;
        toolmanager->setToolPressureSensitivity(true);
        qDebug() << "sensitivity off";
    }
}

void MainWindow::tabletMove(QTabletEvent *t,QPoint ScenePos)
{
    //qDebug() << "tabelt move" << t->pressure() <<","<<t->pos();
    paintArea->tabletMove(t,ScenePos);
}

void MainWindow::tabletPress(QTabletEvent *t,QPoint ScenePos)
{
    //qDebug() << "tabelt Press" << t->pressure();
    paintArea->tabletPress(t,ScenePos);
}

void MainWindow::tabletRelease(QTabletEvent *t,QPoint ScenePos)
{
    paintArea->tabletRelease(t,ScenePos);
    //qDebug() << "tabelt Release" << t->pressure();
}

void MainWindow::on_brushToolButton_clicked()
{
        toolmanager->setActiveTool("brush");
}
