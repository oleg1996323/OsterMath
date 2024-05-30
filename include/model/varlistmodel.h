#pragma once
#include <QTableWidget>
#include <QTableView>
#include <QAbstractListModel>
#include <QWidget>
#include <QHeaderView>
#include <QListView>
#include <QList>
#include <list>
#include <memory>
#include <iterator>
#include <unordered_set>

class VariableBase;

namespace{

class Variables:public QTableView{
public:
    NameColumn(QObject obj):QAbstractListModel(parent){}

    void init(std::unordered_set<std::shared_ptr<VariableBase>>& vars){
        vars_=vars;
        create
    }

    void addNewVariable(const QString& name){

    }

    void deleteVariable(const QString& name){

    }

private:
    QList<std::shared_ptr<VariableBase>>& vars_;
};

class VarListModel:public QTableWidget{
public:
    VarListModel(QWidget* parent):QTableWidget(parent){
          header_ = new QHeaderView(Qt::Horizontal,this);
          header_->

    }

private:
    QHeaderView* header_;
};

}
