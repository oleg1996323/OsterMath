#include "model/varlistmodel.h"

#include <qglobal.h>
#include <QMetaType>
#include <QVariant>
#include <QModelIndex>
#include <QLineEdit>
#include <QStringView>
#include <QDebug>

namespace model{

Variables::Variables(QWidget* obj):
    QAbstractTableModel(obj)
{}

Variables::Variables(QWidget* obj, BaseData* data_base):
    QAbstractTableModel(obj),
    data_base_(data_base)
{
    for(const auto& [var_name,var]:data_base->variables()){
        vars_.push_back({QString(),QString(),var.get(),var->type(),exceptions::EXCEPTION_TYPE::NOEXCEPT});
    }
}

int Variables::rowCount(const QModelIndex& parent = QModelIndex()) const {
    if(parent.isValid()){
        return 0;
    }
    return vars_.size()+1;
}

int Variables::columnCount(const QModelIndex &parent) const {
    //get from deserialized project settings
    return 5;
}

QVariant Variables::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        if(section == (int)HEADER::NAME)
            return QObject::tr("Name");
        else if(section == (int)HEADER::TYPE)
            return QObject::tr("Type");
        else if(section == (int)HEADER::VALUE)
            return QObject::tr("Value");
        else if(section == (int)HEADER::EXPRESSION)
            return QObject::tr("Expression");
        else if(section == (int)HEADER::REMARK)
            return QObject::tr("Notes");
        else return QVariant();
    }
    else return QString::number(section+1);
}

QVariant Variables::data(const QModelIndex& index,int nRole) const {
    if(!index.isValid()){
        return QVariant();
    }
    if(index.row()<0 || index.row()>vars_.size()){
        return QVariant();
    }

    if(nRole == Qt::DisplayRole){
        if(index.row()<vars_.size()){
            switch (index.column()){
            case (int)HEADER::NAME:{
                return QString::fromStdString(vars_.at(index.row()).var_->name());
                break;
            }
            case (int)HEADER::TYPE:{
                return variables::names_of_types[(int)vars_.at(index.row()).type_];
                break;
            }
            case (int)HEADER::EXPRESSION:{
                return vars_.at(index.row()).expr_;
                break;
            }
            case (int)HEADER::VALUE:{
                if(vars_.at(index.row()).err_==exceptions::EXCEPTION_TYPE::NOEXCEPT){
                    if (vars_.at(index.row()).type_&
                    (TYPE_VAL::ARRAY | TYPE_VAL::NUMERIC_ARRAY | TYPE_VAL::STRING_ARRAY))
                        return QString("...");
                    else{
                        std::stringstream stream;
                        vars_.at(index.row()).var_->set_stream(stream);
                        vars_.at(index.row()).var_->print_result();
                        return QString::fromStdString(stream.str());
                    }
                }
                else return QString::fromUtf8(exceptions::get_except_abbr(vars_.at(index.row()).err_));
                break;
            }
            case (int)HEADER::REMARK:{
                return vars_.at(index.row()).note_;
                break;
            }
            default:
                return QVariant();
                break;
            }
        }
        else return QVariant();
    }
    else if(nRole == Qt::EditRole){
        switch (index.column()){
            case (int)HEADER::NAME:{
                return QVariant::fromValue(vars_.at(index.row()).var_);
                break;
            }
            case (int)HEADER::TYPE:{
                return (int)vars_.at(index.row()).type_;
                break;
            }
            case (int)HEADER::EXPRESSION:{
                return vars_.at(index.row()).expr_;
                break;
            }
            case (int)HEADER::VALUE:{

                if(vars_.at(index.row()).err_==exceptions::EXCEPTION_TYPE::NOEXCEPT){
                    std::stringstream stream;
                    vars_.at(index.row()).var_->set_stream(stream);
                    vars_.at(index.row()).var_->print_result();
                    return QString::fromStdString(stream.str());
                }
                else return QString::fromUtf8(exceptions::get_except_abbr(vars_.at(index.row()).err_));
                break;
            }
            case (int)HEADER::REMARK:{
                return vars_.at(index.row()).note_;
                break;
            }
            default:
                return QVariant();
                break;
            }
    }
    else return QVariant();
}

bool Variables::setData(const QModelIndex& index, const QVariant& value, int nRole) {
    if(index.isValid()){
        //for names
        if(nRole == Qt::EditRole){
            switch (index.column()){
            case (int)HEADER::NAME:{
                if(!value.isNull()){
                    if(value.toString()!=""){
                        if(!data_base_->exists(value.toString().toStdString())){
                            if(vars_.size()==index.row()){
                                auto var_ptr = data_base_->add_variable(std::move(value.toString().toStdString())).get();
                                vars_.push_back({QString(),QString(),var_ptr,TYPE_VAL::UNKNOWN,exceptions::EXCEPTION_TYPE::NOEXCEPT});
                                insertRow(rowCount());
                            }
                            else
                                data_base_->rename_var(vars_.at(index.row()).var_->name(),value.toString().toStdString());
                        }
                        return true;
                    }
                    else{
                        if(!vars_.empty()){
                            QString name_var = data(index,Qt::DisplayRole).toString();
                            data_base_->erase(name_var.toStdString());
                            assert(QMetaType::isRegistered(QMetaType::type("std::string")));
                            assert(!data_base_->exists(data(index,Qt::DisplayRole).toString().toStdString()));
                            removeRow(index.row());
                        }
                        return true;
                    }
                }
                return false;
                break;
            }
            case (int)HEADER::TYPE:{
                switch(value.value<TYPE_VAL>()){
                case TYPE_VAL::UNKNOWN:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::UNKNOWN;
                    }
                    return true;
                    break;
                case TYPE_VAL::ARRAY:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::ARRAY;
                        //vars_.at(index.row())->node()->insert(std::make_shared<ArrayNode>());
                    }
                    return true;
                    break;
                case TYPE_VAL::NUMERIC_ARRAY:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::NUMERIC_ARRAY;
                    }
                    return true;
                    break;
                case TYPE_VAL::STRING_ARRAY:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::STRING_ARRAY;
                    }
                    return true;
                    break;
                case TYPE_VAL::STRING:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::STRING;
                    }
                    return true;
                    break;
                case TYPE_VAL::VALUE:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::VALUE;
                    }
                    return true;
                    break;
                default:
                    return true;
                    break;
                }
                break;
            }
            case (int)HEADER::EXPRESSION:{
                vars_.at(index.row()).expr_=value.toString();
                QString var_expr = QString("VAR(!('%1')#%2)").
                        arg(data_base_->name().data()).
                        arg(vars_.at(index.row()).var_->name().data())+
                        vars_.at(index.row()).expr_;
                std::stringstream stream;
                stream<<var_expr.toStdString();
                qDebug()<<var_expr;
                data_base_->setstream(stream);
                vars_.at(index.row()).err_ = exception_handler([&]()->void{
                    data_base_->read_new();
                }/*, qobject_cast<QWidget*>(QAbstractItemModel::parent())*/);
                qDebug()<<"Parents size at"<<QString::fromStdString(vars_.at(index.row()).var_->name())<<": "<<vars_.at(index.row()).var_->node()->parents().size();
                if(vars_.at(index.row()).err_==exceptions::EXCEPTION_TYPE::NOEXCEPT)
                    vars_.at(index.row()).err_=exception_handler([&]()->void{
                        vars_.at(index.row()).var_->refresh();
                        vars_.at(index.row()).type_ = vars_.at(index.row()).var_->type();
                    }/*, qobject_cast<QWidget*>(QAbstractItemModel::parent())*/);
                emit dataChanged(createIndex(0,0), createIndex(rowCount(),0));
                return true;
                break;
            }
            case (int)HEADER::VALUE:{
                return true;
                break;
            }
            case (int)HEADER::REMARK:{
                return true;
                break;
            }
            }
        }
    }
    return false;
}

#include <QFlags>

Qt::ItemFlags Variables::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
}

bool Variables::insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
    if(parent.isValid())
        return false;

    beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
    endInsertRows();
    return true;
}

bool Variables::insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) {
    if(parent.isValid())
        return false;
    return true;
    //        beginInsertColumns(QModelIndex(),column,column+count-1);
    //        for(int i = 0;i<count;++i){

    //        }

}

bool Variables::removeRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
    if(parent.isValid())
        return false;

    beginRemoveRows(QModelIndex(),nRow,nRow+nCount-1);
    for(int i = 0; i<nCount; ++i){
        vars_.erase(vars_.begin()+nRow);
    }
    endRemoveRows();
    return true;
}

void Variables::set_default_header_pos(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    //порядок колонок
    sets_->beginGroup("VarListTable/header");
    sets_->setValue("name",QVariant().fromValue(HEADER::NAME));
    sets_->setValue("type",QVariant().fromValue(HEADER::TYPE));
    sets_->setValue("value",QVariant().fromValue(HEADER::VALUE));
    sets_->setValue("expression",QVariant().fromValue(HEADER::EXPRESSION));
    sets_->setValue("remark",QVariant().fromValue(HEADER::REMARK));
    sets_->endGroup();
}

void Variables::get_header_pos(){

}

void Variables::__load_settings__(){

}

void Variables::__save_settings__(){

}

BaseData* Variables::get_data() const{
    return data_base_;
}

void Variables::set_data(BaseData* data_base){
    data_base_ = data_base;
}

}
