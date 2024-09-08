#pragma once
#include "model/def.h"
#include <QWidget>
#include <QAbstractItemModel>
#include <QList>
#include "kernel/application.h"
#include "kernel/settings.h"
#include "kernel/exception.h"
#include <vector>

namespace model{

class NodeView:public QAbstractTableModel{
    Q_OBJECT
public:
    //TODO
    enum MODE_REPRESENTATION{
        Table,
        Sequential
    };

    ~NodeView() = default;

    NodeView(QObject* parent);

    void rename(const QString& name) noexcept;
    void set_representable_node(Node*, size_t);
    void set_representable_child_node(size_t id);
    void reset_representable_node();
    INFO_NODE get_node() const{
        if(!sequence_node_.empty())
            return sequence_node_.back();
        else return INFO_NODE();
    }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool insertRows(int nRow, int nCount, const QModelIndex& parent) override;
    virtual bool insertColumns(int column, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int nRow, int nCount, const QModelIndex& parent) override;
    virtual bool removeColumns(int nRow, int nCount, const QModelIndex& parent) override;

    int get_rows_cached_count() const;
    int get_columns_cached_count() const;

    bool insert_row_before(int nRow, int nCount);
    bool insert_column_before(int nCol, int nCount);
    bool insert_row_after(int nRow, int nCount);
    bool insert_column_after(int nCol, int nCount);

private:
    MODE_REPRESENTATION mode_ = MODE_REPRESENTATION::Table;
    std::vector<INFO_NODE> sequence_node_;
    mutable int cached_row_count_ = 0;
    mutable int cached_column_count_ = 0;
    mutable int id_max_row_childs_ = -1;

    INFO_NODE get_showed_node(QModelIndex index) const;
    std::vector<INFO_NODE> get_sequence_ids_at_set_data(QModelIndex index);
    bool __convert_value_to_array__(Node* parent,int id,size_t sz,bool before);
};
}
