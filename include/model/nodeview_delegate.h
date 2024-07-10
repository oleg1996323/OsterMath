#pragma once
#include <QWidget>
#include <QAbstractItemDelegate>
#include <QMetaType>
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

class NodeViewDelegate:public QAbstractItemDelegate{
    Q_OBJECT
public:

    NodeViewDelegate(QWidget* obj);

    ~NodeViewDelegate() = default;

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;

    void set_default_header_pos();

    void get_header_pos();

    void __load_settings__();
    void __save_settings__();

    void refresh(){

    }

signals:
    void show_value();

private:

};

}