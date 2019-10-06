#include "layerlistview.h"

LayerListView::LayerListView(QWidget *parent) : QListView (parent)
{
    //connect( this, SIGNAL(clicked( const QModelIndex &  )), this, SLOT(clickedSlot( const QModelIndex &  )) );
}



void LayerListView::clicked(const QModelIndex &index)
{
   if( index.isValid() )
   {
      // Checkbox toggle

      if( index.column() == 0 )
      {
         QVariant beforeValue = this->model()->data( index );

         this->model()->setData( index, QVariant::fromValue( ! beforeValue.toBool() ) );
      }
      else
      if( index.column() == 1 )
      {
         this->selectionModel()->select( index, QItemSelectionModel::Toggle );
      }
   }
}

void LayerListView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    //static_cast<layerlistmodel*>(this->model())->getManager()->setActiveLayer(static_cast<layeritem*>(current.internalPointer()));
}
