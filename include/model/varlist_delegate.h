#pragma once
#include <QWidget>
#include <QAbstractItemDelegate>
#include <QMetaType>
#include <QStyledItemDelegate>
#include <QComboBox>
#include "types.h"
#include "kernel/settings.h"
#include "kernel/def.h"
#include "arithmetic_types.h"

#include "exception/exception.h"
#include "model/def.h"
//#include <dlfcn.h>

class VariableBase;

namespace model{

class VariablesDelegate:public QStyledItemDelegate{
    Q_OBJECT
public:

    VariablesDelegate(QObject* obj);

    ~VariablesDelegate() = default;

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void set_default_header_pos();

    void get_header_pos();

    void __load_settings__();
    void __save_settings__();

    void refresh(){

    }

signals:
    void show_node(Node*,size_t) const;

private:
};

}
