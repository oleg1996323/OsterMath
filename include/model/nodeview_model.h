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
    struct SubNodes{
        SubNodes(const SubNodes&) = default;
        int id_;
        Node* node_;
        QList<SubNodes> openned_;
    };

public:
    enum MODE_REPRESENTATION{
        Table,
        Sequential
    };

    ~NodeView() = default;

    NodeView(QObject* parent);

    void rename(const QString& name) noexcept;
    void set_representable_node(Node*);
    void set_representable_child_node(size_t id);
    void reset_representable_node();
    Node* get_node() const{
        return sequence_node_.back();
    }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    //virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    virtual bool insertRows(int nRow, int nCount, const QModelIndex& parent) override;
    virtual bool insertColumns(int column, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int nRow, int nCount, const QModelIndex& parent) override;
    virtual bool removeColumns(int nRow, int nCount, const QModelIndex& parent) override;

private:
    QList<SubNodes> openned_;
    std::unique_ptr<NodeView> child_;
    MODE_REPRESENTATION mode_ = MODE_REPRESENTATION::Table;
    std::vector<Node*> sequence_node_;
    mutable int cached_row_count_ = 0;
    mutable int cached_column_count_ = 0;

    std::shared_ptr<Node>& get_showed_node(QModelIndex index) const;
};
}
