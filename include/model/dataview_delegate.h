#pragma once
#include <QTableWidget>
#include <QTableView>
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include <QWidget>
#include <QHeaderView>
#include <QListView>
#include <QModelIndex>
#include <deque>
#include <QSettings>
#include <list>
#include <memory>
#include <iterator>
#include <unordered_set>
#include <QSettings>
#include <QStyledItemDelegate>
#include <QComboBox>
#include "types.h"
#include <string_view>
#include <string>
#include "kernel/settings.h"
#include "kernel/def.h"
#include "arithmetic_types.h"
#include <qmetatype.h>
#include "exception/exception.h"
#include "model/def.h"
#include <QAbstractItemDelegate>
//#include <dlfcn.h>

class VariableBase;

namespace model{

class DataViewDelegate:public QAbstractItemDelegate{
    Q_OBJECT
public:

    DataViewDelegate(QWidget* obj);

    ~DataViewDelegate() = default;

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
