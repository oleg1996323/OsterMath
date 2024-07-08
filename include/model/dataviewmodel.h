#pragma once
#include "model/def.h"
#include <QWidget>
#include <QAbstractItemModel>
#include "kernel/application.h"
#include "kernel/settings.h"
#include "kernel/exception.h"
#include <stack>

namespace model{

class DataView:public QAbstractItemModel{
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

    DataView(QObject* parent);

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
    virtual bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;
    virtual bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;

private:
    QList<SubNodes> openned_;
    ChildsMeasure measure_;
    std::unique_ptr<DataView> child_;
    MODE_REPRESENTATION mode_;
    std::vector<Node*> sequence_node_;
};
}
