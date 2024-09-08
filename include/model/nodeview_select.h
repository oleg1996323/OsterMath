#pragma once
#include "model/def.h"
#include "kernel/application.h"
#include <QContextMenuEvent>
#include <QItemSelection>
#include <QItemSelectionModel>

namespace model{
class NodeViewSelectionModel:public QItemSelectionModel{
    Q_OBJECT
public:
    enum ModeSelection{
        NONE = 0x0000,
        ROWS_SELECTION = 0x0001,
        COLUMNS_SELECTION = 0x0002,
        ALL_SELECTION = 0x0004,
        RANGE_SELECTION = 0x0008,
        CUSTOM_SELECTION = 0x0010
    };
    NodeViewSelectionModel(QAbstractItemModel* model = nullptr):QItemSelectionModel(model){}
    ~NodeViewSelectionModel() = default;

//    virtual void select(const QModelIndex &index, QItemSelectionModel::SelectionFlags command) override;
    virtual void select(const QItemSelection &selection, QItemSelectionModel::SelectionFlags command) override;
    bool is_columns() const;
    bool is_rows() const;
    bool is_range() const;
    bool is_empty() const;
    QModelIndex first_index() const;
private:
    ModeSelection mode_ = ModeSelection::NONE;
};
}
