#pragma once
#include <QContextMenuEvent>
#include <QItemSelection>
#include <QItemSelectionModel>

namespace model{
class NodeViewSelectionModel:public QItemSelectionModel{
    Q_OBJECT
public:
    NodeViewSelectionModel():QItemSelectionModel(){
    }

//    virtual void clear();
//    virtual void clearCurrentIndex();
//    virtual void reset();
//    virtual void select(const QModelIndex &index, QItemSelectionModel::SelectionFlags command);
//    virtual void select(const QItemSelection &selection, QItemSelectionModel::SelectionFlags command);
//    virtual void setCurrentIndex(const QModelIndex &index, QItemSelectionModel::SelectionFlags command);
};
}
