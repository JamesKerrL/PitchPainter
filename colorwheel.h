#ifndef COLORWHEEL_H
#define COLORWHEEL_H


#include <QWidget>
#include <QSlider>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
class ColorWheel : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWheel(QWidget *parent = 0);

    virtual QSize sizeHint () const;
    virtual QSize minimumSizeHint () const;
    QColor color();


public slots:
    void setColor(const QColor &color);

signals:
    void colorChange(const QColor &color);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);
private:
    QSize initSize;
    QImage wheelImage;
    QImage squareImage;
    QPixmap wheel;
    bool mouseDown;
    QPoint lastPos;
    int margin;
    int wheelWidth;
    QRegion wheelRegion;
    QRegion squareRegion;


    QSlider *hueSlider;
    QGridLayout* layout;
    QHBoxLayout* boxLayout;
    QLabel *hueLabel;

    QColor current;
    bool inWheel;
    bool inSquare;
    QColor posColor(const QPoint &point);
    void drawWheelImage(const QSize &newSize);
    void drawIndicator(const int &hue);
    void drawPicker(const QColor &color);
    void drawSquareImage(const int &hue);
    void composeWheel();
private slots:
    void hueChanged(const int &hue);
    void svChanged(const QColor &newcolor);
};


#endif // COLORWHEEL_H
