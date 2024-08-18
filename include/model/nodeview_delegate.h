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

class NodeViewDelegate:public QStyledItemDelegate{
    Q_OBJECT
public:

    NodeViewDelegate(QObject*);

    ~NodeViewDelegate() = default;

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    //virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;

    void __load_settings__();
    void __save_settings__();

    void refresh(){

    }

private:
    //virtual void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
};
}
