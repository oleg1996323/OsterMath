#include "model/varlist_model.h"

#include <qglobal.h>
#include <QMetaType>
#include <QVariant>
#include <QModelIndex>
#include <QLineEdit>
#include <QStringView>
#include <QDebug>
#include <QSaveFile>

namespace model{

Variables::Variables(QObject* obj, BaseData* data_base):
    QAbstractTableModel(obj),
    data_base_(data_base)
{
    for(const auto& [var_name,var]:data_base->variables()){
        vars_.push_back({QString(),QString(),var->node(),var->type(),exceptions::EXCEPTION_TYPE::NOEXCEPT});
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
                const std::shared_ptr<Node>& var=vars_.at(index.row()).node_;
                if(!var || var->type()!=NODE_TYPE::VARIABLE)
                    return QVariant();
                return QString::fromStdString(dynamic_cast<VariableNode*>(var.get())->variable()->name());
                break;
            }
            case (int)HEADER::TYPE:{
                return variables::names_of_types.value(vars_.at(index.row()).type_);
                break;
            }
            case (int)HEADER::EXPRESSION:{
                return vars_.at(index.row()).expr_;
                break;
            }
            case (int)HEADER::VALUE:{
                if(vars_.at(index.row()).err_==exceptions::EXCEPTION_TYPE::NOEXCEPT){
                    if (parent() && (vars_.at(index.row()).type_ == TYPE_VAL::ARRAY
                            || vars_.at(index.row()).type_ == TYPE_VAL::NUMERIC_ARRAY
                            || vars_.at(index.row()).type_ == TYPE_VAL::STRING_ARRAY))
                        return QString("...");
                    else{
                        std::stringstream stream;
                        const std::shared_ptr<Node>& var=vars_.at(index.row()).node_;
                        if(!var || var->type()!=NODE_TYPE::VARIABLE)
                            return QVariant();
                        dynamic_cast<VariableNode*>(var.get())->variable()->set_stream(stream);
                        dynamic_cast<VariableNode*>(var.get())->variable()->print_result();
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
                const std::shared_ptr<Node>& var=vars_.at(index.row()).node_;
                if(!var || var->type()!=NODE_TYPE::VARIABLE)
                    return QVariant();
                return QVariant::fromValue(dynamic_cast<VariableNode*>(var.get())->variable());
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
                if(!vars_.at(index.row()).node_)
                    return QVariant();
                return QVariant::fromValue(vars_.at(index.row()).node_);
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
        if(nRole == Qt::DisplayRole){
            switch (index.column()){
            case (int)HEADER::NAME:{
                if(!value.isNull()){
                    if(value.toString()!=""){
                        if(!data_base_->exists(value.toString().toStdString())){
                            if(vars_.size()==index.row()){
                                const std::shared_ptr<Node>& var_ptr = data_base_->add_variable(std::move(value.toString().toStdString())).get()->node();
                                vars_.push_back({QString(),QString(),var_ptr,TYPE_VAL::UNKNOWN,exceptions::EXCEPTION_TYPE::NOEXCEPT});
                                insertRow(rowCount(), QModelIndex());
                            }
                            else{
                                const std::shared_ptr<Node>& var = vars_.at(index.row()).node_;
                                if(!var || var->type()!=NODE_TYPE::VARIABLE)
                                    return false;
                                data_base_->rename_var(dynamic_cast<VariableNode*>(var.get())->variable()->name(),value.toString().toStdString());
                            }
                        }
                        else{
                            if(vars_.size()==index.row()){
                                const std::shared_ptr<Node>& var = data_base_->get(value.toString().toStdString())->node();
                                if((!var || var->type()!=NODE_TYPE::VARIABLE))
                                    return false;
                                if(!contains(var)){
                                    vars_.push_back({QString(),QString(),var,TYPE_VAL::UNKNOWN,exceptions::EXCEPTION_TYPE::NOEXCEPT});
                                    insertRow(rowCount(), QModelIndex());
                                }
                            }
                            else
                                data_base_->rename_var(dynamic_cast<VariableNode*>(vars_.at(index.row()).node_.get())->variable()->name(),value.toString().toStdString());
                        }
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                return false;
                break;
            }
            case (int)HEADER::TYPE:{
                switch(value.value<TYPE_VAL>()){
                case TYPE_VAL::UNKNOWN:
                    if(vars_.at(index.row()).node_->type_val()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).node_->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::UNKNOWN;
                    }
                    return true;
                    break;
                case TYPE_VAL::ARRAY:
                    if(vars_.at(index.row()).node_->type_val()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).node_->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::ARRAY;
                        //vars_.at(index.row())->node()->insert(std::make_shared<ArrayNode>());
                    }
                    return true;
                    break;
                case TYPE_VAL::NUMERIC_ARRAY:
                    if(vars_.at(index.row()).node_->type_val()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).node_->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::NUMERIC_ARRAY;
                    }
                    return true;
                    break;
                case TYPE_VAL::STRING_ARRAY:
                    if(vars_.at(index.row()).node_->type_val()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).node_->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::STRING_ARRAY;
                    }
                    return true;
                    break;
                case TYPE_VAL::STRING:
                    if(vars_.at(index.row()).node_->type_val()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).node_->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::STRING;
                    }
                    return true;
                    break;
                case TYPE_VAL::VALUE:
                    if(vars_.at(index.row()).node_->type_val()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).node_->release_childs();
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
                NODE_STRUCT res = parse_to_insert_item(value.toString());
                bool success = true;
                success = res.err_&exceptions::EXCEPTION_TYPE::NOEXCEPT?true:false;
                vars_.at(index.row()) = res;
                if(vars_.at(index.row()).node_->has_child(0))
                    vars_.at(index.row()).node_->child(0)=std::move(res.node_);
                else
                    vars_.at(index.row()).node_->insert_back(std::move(res.node_));
                emit dataChanged(createIndex(0,0), createIndex(rowCount(),0));
                return success;
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
    if(index.column()!=(int)HEADER::TYPE || index.column()!=(int)HEADER::VALUE)
        return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
    else return (index.isValid())?(flags):flags;
}

bool Variables::insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
    if(parent.isValid())
        return false;

    beginInsertRows(parent,nRow,nRow+nCount-1);
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

bool Variables::contains(const std::shared_ptr<Node>& var) const{
    return std::find_if(vars_.begin(),vars_.end(),[var](const NODE_STRUCT& var_data){
       return var_data.node_.get()==var.get() && var->type()==NODE_TYPE::VARIABLE;
    })!=vars_.end();
}

//void Variables::refresh(NODE_STRUCT node_data){

//}

}
