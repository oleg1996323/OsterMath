#pragma once
#include <QWidget>
#include <QAbstractTableModel>
#include "kernel/application.h"
#include "kernel/settings.h"
#include "kernel/exception.h"
#include "data.h"
#include "types.h"
#include "def.h"

namespace model{

class VarData:public QAbstractTableModel{
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

private:
    ChildsMeasure measure_;
    VariableBase* var_ = nullptr;
    MODE_REPRESENTATION mode_;
};
}
