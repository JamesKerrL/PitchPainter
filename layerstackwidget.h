#ifndef LAYERSTACKWIDGET_H
#define LAYERSTACKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListView>
#include "layerlistview.h"
#include <QStringListModel>
#include "layerlistmodel.h"
#include "layermanager.h"
class layerstackwidget : public QWidget
{
    Q_OBJECT
public:
    explicit layerstackwidget(QWidget *parent = nullptr);
    QPushButton *addLayerButton;
    QVBoxLayout *mainLayout;
    QListView *layerListWidget;
    LayerListView *customLayerView;
    layerlistmodel *layerModel;
signals:

public slots:
    void addLayerClicked();
};

#endif // LAYERSTACKWIDGET_H
