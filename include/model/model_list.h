#pragma once

#include <QAbstractListModel>
#include <QModelIndex>
#include <QModelIndexList>

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
