#pragma once

#include <QAbstractListModel>
#include <QModelIndex>
#include <QModelIndexList>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QList>

class ModelList:public QAbstractTableModel{
    Q_OBJECT
public:
    ModelList(QObject* parent):QAbstractTableModel(parent){

    }

    bool setData(const QModelIndex& index, const QVariant& value, int role){
        if(index.isValid() && role == Qt::EditRole){
            //list replace value
        }
    }
};

class VarListItems: public QAbstractListModel{
    QList<int> m_list;

public:
    VarListItems(const QList<int>& list,QWidget* parent):
        QAbstractListModel(parent),
        m_list(list){
        //this->setHeaderData();
    }

    QVariant data(const QModelIndex& index,int nRole) const{
        if(!index.isValid()){
            return QVariant();
        }
        if(index.row()<0 || index.row()>=m_list.size()){
            return QVariant();
        }
        return (nRole==Qt::DisplayRole || nRole==Qt::EditRole)
                ? m_list.at(index.row())
                : QVariant();
    }

    bool setData(const QModelIndex& index, const QVariant& value, int nRole){
        if(index.isValid() && nRole == Qt::EditRole){
            m_list.replace(index.row(),value.value<int>());
            emit dataChanged(index,index);
            return true;
        }
        return false;
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const{
        if(parent.isValid()){
            return 0;
        }
        return m_list.size();
    }

    QVariant header_data_(int nSection,Qt::Orientation orientation,int nRole = Qt::DisplayRole) const{
        if(nRole != Qt::DisplayRole){
            return QVariant();
        }
        return (orientation == Qt::Horizontal) ? QString("Number"):QString::number(nSection);
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override{
        Qt::ItemFlags flags = QAbstractListModel::flags(index);
        return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
    }

    bool insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()){
        if(parent.isValid())
            return false;

        beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            m_list.insert(nRow,0);
        }
        endInsertRows();
        return true;
    }

    bool removeRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()){
        if(parent.isValid())
            return false;

        beginRemoveRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            m_list.removeAt(nRow);
        }
        endRemoveRows();
        return true;
    }
};
