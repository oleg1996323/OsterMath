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
//#include <dlfcn.h>

#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
    #ifdef MODEL_SHARED
        #ifdef __GNUC__
            #define MODEL_SHARED_EXPORT_DECL __attribute__ ((dllexport))
        #else
            #define MODEL_SHARED_EXPORT_DECL __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define MODEL_SHARED_EXPORT_DECL __attribute__ ((dllimport))
        #else
            #define MODEL_SHARED_EXPORT_DECL __declspec(dllimport)
        #endif
    #endif
#else
    #define MODEL_SHARED_EXPORT_DECL __attribute__ ((visibility ("default")))
#endif

#define MODEL_SHARED_EXPORT extern "C" MODEL_SHARED_EXPORT_DECL



class VariableBase;

namespace model{
enum class HEADER{
    NAME,
    TYPE,
    VALUE,
    EXPRESSION,
    REMARK
};

class Variables:public QStyledItemDelegate,public QAbstractTableModel{
public:
    struct VAR_STRUCT{
        QString expr_;
        QString note_;
        VariableBase* var_;
        TYPE_VAL type_;
        exceptions::EXCEPTION_TYPE err_;
    };

    Variables(QWidget* obj);

    Variables(QWidget* obj, BaseData* data_base);

    ~Variables() = default;

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

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void set_default_header_pos();

    void get_header_pos();

    void __load_settings__();
    void __save_settings__();

private:
    std::deque<VAR_STRUCT> vars_;
    QMap<TYPE_VAL,uint8_t> header_pos_;
    BaseData* data_base_;
};

}

Q_DECLARE_METATYPE(TYPE_VAL)
Q_DECLARE_METATYPE(model::HEADER)
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(Value_t)
Q_DECLARE_METATYPE(Node*)
