#pragma once
#include <QWidget>
#include <QAbstractItemModel>
#include "kernel/application.h"
#include "kernel/settings.h"
#include "kernel/exception.h"
#include "data.h"
#include "types.h"
#include "def.h"

namespace model{

class VarData:public QAbstractItemModel{
public:
    enum MODE_REPRESENTATION{
        Table,
        Sequential
    };

    VarData(QWidget* parent, VariableBase* var);

    void rename(const QString& name) noexcept;
    void set_representable_variable(VariableBase*);
    void reset_representable_variable();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;
    virtual bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;

private:
    ChildsMeasure measure_;
    VariableBase* var_ = nullptr;
    MODE_REPRESENTATION mode_;
};
}
