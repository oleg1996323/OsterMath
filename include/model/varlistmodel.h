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
#include <types.h>

class VariableBase;

namespace model{
    Q_NAMESPACE
enum class HEADER{
    NAME,
    TYPE,
    VALUE,
    EXPRESSION,
    REMARK
};

#include <QCoreApplication>

class Variables:public QAbstractTableModel{
public:
    Variables(QObject* obj):
        QAbstractTableModel(obj),
        sets_(QSettings(QCoreApplication::organizationName(),QCoreApplication::applicationName(),this))
    {}

    void init(const QList<std::shared_ptr<VariableBase>>& vars){
        vars_=vars;
    }

    void addNewVariable(const QString& name){

    }

    void deleteVariable(const QString& name){

    }

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override{
        if(role != Qt::DisplayRole)
            return QVariant();
        if(orientation == Qt::Horizontal){
            if(section == 0)
                return QObject::tr("Имя");
            else if(section == 1)
                return QObject::tr("Тип");
            else if(section == 2)
                return QObject::tr("Значение");
            else return QVariant();
        }
        else return QString::number(section);
    }

    virtual QVariant data(const QModelIndex& index,int nRole) const override{
        if(!index.isValid()){
            return QVariant();
        }
        if(index.row()<0 || index.row()>=vars_.size()){
            return QVariant();
        }
        return (nRole==Qt::DisplayRole || nRole==Qt::EditRole)
                ? vars_.at(index.row())
                : QVariant();
    }

    virtual bool setData(const QModelIndex& index, const QVariant& value, int nRole) override{
        if(index.isValid() && nRole == Qt::EditRole){
            vars_.replace(index.row(),value.value<QString>());
            emit dataChanged(index,index);
            return true;
        }
        return false;
    }

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        if(parent.isValid()){
            return 0;
        }
        return vars_.size();
    }

    virtual int columnCount(const QModelIndex &parent) const override{
        if(parent.isValid()){
            return 0;
        }
        return 5;
    }

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override{
        Qt::ItemFlags flags = QAbstractTableModel::flags(index);
        return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
    }

    virtual bool insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) override{
        if(parent.isValid())
            return false;

        beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            vars_.insert(nRow,0);
        }
        endInsertRows();
        return true;
    }

    virtual bool insertColumns(int column, int count, const QModelIndex &parent) const override{
        if(parent.isValid())
            return false;
        beginInsertColumns(QModelIndex(),column,column+count-1);
        for(int i = 0;i<count;++i){

        }
    }

    virtual bool removeRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) override{
        if(parent.isValid())
            return false;

        beginRemoveRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            vars_.removeAt(nRow);
        }
        endRemoveRows();
        return true;
    }

    void set_default_header_pos(){
        sets_.setValue("VarListTable/header/name",0);
        sets_.setValue("VarListTable/header/type",1);
        sets_.setValue("VarListTable/header/value",2);
        sets_.setValue("VarListTable/header/expression",3);
        sets_.setValue("VarListTable/header/remark",4);
    }

    void get_header_pos(){
        insertColumns();
    }

private:
    QList<std::shared_ptr<VariableBase>> vars_;
    QSettings sets_;
};

}
