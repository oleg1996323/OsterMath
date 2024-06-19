#include "model/varlistmodel.h"
#include "arithmetic_types.h"
#include <QModelIndex>

namespace model{

    Variables::Variables(QObject* obj):
        QAbstractTableModel(obj)
    {}

    Variables::Variables(QObject* obj, BaseData* data_base):
        QAbstractTableModel(obj),
        data_base_(data_base)
    {
        for(const auto& [var_name,var]:data_base->variables())
            vars_.push_back(var.get());
    }

    void Variables::addNewVariable(const QString& name){

    }

    void Variables::deleteVariable(const QString& name){

    }

     QVariant Variables::headerData(int section, Qt::Orientation orientation, int role) const {
        if(role != Qt::DisplayRole)
            return QVariant();
        if(orientation == Qt::Horizontal){
            if(section == (int)HEADER::NAME)
                return QObject::tr("Имя");
            else if(section == (int)HEADER::TYPE)
                return QObject::tr("Тип");
            else if(section == (int)HEADER::VALUE)
                return QObject::tr("Значение");
            else if(section == (int)HEADER::EXPRESSION)
                return QObject::tr("Выражение");
            else if(section == (int)HEADER::REMARK)
                return QObject::tr("Примечания");
            else return QVariant();
        }
        else return QString::number(section);
    }

     QVariant Variables::data(const QModelIndex& index,int nRole) const {
        if(!index.isValid()){
            return QVariant();
        }
        if(index.row()<0 || index.row()>=vars_.size()){
            return QVariant();
        }

        if(index.column()==0)
            return (nRole==Qt::DisplayRole || nRole==Qt::EditRole)
                    ? QString::fromStdString(std::string(vars_.at(index.row())->name()))
                    : QVariant();
        else return QVariant();
    }

     bool Variables::setData(const QModelIndex& index, const QVariant& value, int nRole) {
        if(index.isValid() && nRole == Qt::EditRole){
            //for names
            if(index.column()==(int)HEADER::NAME){
                if(vars_.size()==index.row()){
                    vars_.push_back(data_base_->add_variable(value.value<std::string>()).get());
                }
                else
                    data_base_->rename_var(std::string(vars_.at(index.row())->name()),value.value<std::string>());
            }
            //for types
            else if(index.column()==(int)HEADER::TYPE){
                if(vars_.size()>=index.row()){
                    switch(value.value<TYPE_VAL>()){
                    case TYPE_VAL::UNKNOWN:
                        vars_.at(index.row())->node()->release_childs();
                        break;
                    case TYPE_VAL::STRING:
                        //vars_.at(index.row())->node()->insert(std::make_shared<ArrayNode>());
                        break;
                    }
                    case TYPE_VAL::VALUE:{
                        vars_.at(index.row())->node()->insert(std::make_shared<ValueNode>(0));
                        break;
                    }
                    case TYPE_VAL::{
                        break;
                    }


                    data_base_->get(data(index.siblingAtColumn((int)HEADER::TYPE),Qt::DisplayRole).value<std::string>());
                }
                else
                    data_base_->rename_var(std::string(vars_.at(index.row())->name()),value.value<std::string>());
            }
            emit dataChanged(index,index);
            return true;
        }
        return false;
    }

     int Variables::rowCount(const QModelIndex& parent = QModelIndex()) const {
        if(parent.isValid()){
            return 0;
        }
        return vars_.size();
    }

     int Variables::columnCount(const QModelIndex &parent) const {
        if(parent.isValid()){
            return 0;
        }
        return 5;
    }

     Qt::ItemFlags Variables::flags(const QModelIndex& index) const {
        Qt::ItemFlags flags = QAbstractTableModel::flags(index);
        return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
    }

     bool Variables::insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
        if(parent.isValid())
            return false;

        beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            vars_.insert(nRow,0);
        }
        endInsertRows();
        return true;
    }

     bool Variables::insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) {
        if(parent.isValid())
            return false;
//        beginInsertColumns(QModelIndex(),column,column+count-1);
//        for(int i = 0;i<count;++i){

//        }
    }

     bool Variables::removeRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
        if(parent.isValid())
            return false;

        beginRemoveRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            vars_.removeAt(nRow);
        }
        endRemoveRows();
        return true;
    }

    void Variables::set_default_header_pos(){
        QSettings* sets_ = kernel::settings::Program::get_settings();
        //порядок колонок
        sets_->beginGroup("VarListTable/header");
            sets_->setValue("name",0);
            sets_->setValue("type",1);
            sets_->setValue("value",2);
            sets_->setValue("expression",3);
            sets_->setValue("remark",4);
        sets_->endGroup();
    }

    void Variables::get_header_pos(){

    }

    void Variables::__load_settings__(){

    }

    void Variables::__save_settings__(){

    }


}
