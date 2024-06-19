#pragma once
#include <QTableWidget>
#include <QTableView>
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include <QWidget>
#include <QHeaderView>
#include <QListView>
#include <QModelIndex>
#include <QList>
#include <QSettings>
#include <list>
#include <memory>
#include <iterator>
#include <unordered_set>
#include <QSettings>
#include "types.h"
#include <string_view>
#include "kernel/settings.h"

Q_DECLARE_METATYPE(std::string)

class VariableBase;

namespace model{
enum class HEADER{
    NAME,
    TYPE,
    VALUE,
    EXPRESSION,
    REMARK
};

class Variables:public QAbstractTableModel{
public:
    Variables(QObject* obj);

    Variables(QObject* obj, BaseData* data_base);

    void addNewVariable(const QString& name);

    void deleteVariable(const QString& name);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual QVariant data(const QModelIndex& index,int nRole) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int nRole) override;

    virtual int rowCount(const QModelIndex& parent) const override;

    virtual int columnCount(const QModelIndex &parent) const override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual bool insertRows(int nRow, int nCount, const QModelIndex& parent) override;

    virtual bool insertColumns(int column, int count, const QModelIndex &parent) override;

    virtual bool removeRows(int nRow, int nCount, const QModelIndex& parent) override;

    void set_default_header_pos();

    void get_header_pos();

    void __load_settings__();
    void __save_settings__();

private:
    BaseData* data_base_;
    QList<const VariableBase*> vars_;
};

}
