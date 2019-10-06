#include "layerstackwidget.h"

layerstackwidget::layerstackwidget(QWidget *parent) : QWidget(parent)
{
    addLayerButton = new QPushButton();
    mainLayout = new QVBoxLayout();
    layerListWidget = new QListView();
    this->setLayout(mainLayout);
    mainLayout->addWidget(addLayerButton);
    //connect(this, )
    //mainLayout->addWidget(layerListWidget);
    customLayerView = new LayerListView();
    mainLayout->addWidget(customLayerView);
    customLayerView->setAcceptDrops(true);
    customLayerView->setDragEnabled(true);
    customLayerView->setDragDropMode(QAbstractItemView::InternalMove);
    //customLayerView->setDragDropOverwriteMode(false);
    layerManager *manager = new layerManager();
    layerModel = new layerlistmodel(manager);
    customLayerView->setModel(layerModel);
    connect(addLayerButton,&QPushButton::clicked,manager,&layerManager::addLayerClicked);
}

void layerstackwidget::addLayerClicked()
{

}
