#pragma once
#include <QAbstractTableModel>
#include <QWidget>
#include <QVariant>
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

namespace model{

class Variables:public QAbstractTableModel{
    Q_OBJECT
public:
    struct VAR_STRUCT{
        QString expr_;
        QString note_;
        VariableBase* var_;
        TYPE_VAL type_;
        exceptions::EXCEPTION_TYPE err_;
    };

    Variables(QObject* parent, BaseData* data_base);

    ~Variables() = default;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual QVariant data(const QModelIndex& index,int nRole) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int nRole) override;

    virtual int rowCount(const QModelIndex& parent) const override;

    virtual int columnCount(const QModelIndex &parent) const override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual bool insertRows(int nRow, int nCount, const QModelIndex& parent) override;

    virtual bool insertColumns(int column, int count, const QModelIndex &parent) override;

    virtual bool removeRows(int nRow, int nCount, const QModelIndex& parent) override;

    void __load_settings__();
    void __save_settings__();

    void refresh(){

    }

    bool contains(VariableBase*);

    void set_data(BaseData*);

    BaseData* get_data() const;

signals:
    void show_value();

private:
    std::deque<VAR_STRUCT> vars_;
    QMap<TYPE_VAL,uint8_t> header_pos_;
    BaseData* data_base_;
};

}
