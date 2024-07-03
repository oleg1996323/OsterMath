#include "model/dataviewmodel.h"
#include "types.h"

namespace model{

VarData::VarData(QWidget* parent, VariableBase* var):
    QAbstractItemModel(parent),
    var_(var)
{
    if(var->is_array())
        define_section_subelements(measure_,var_->result().get<ArrayNode*>());
}

int VarData::rowCount(const QModelIndex &parent) const{
    if(mode_|MODE_REPRESENTATION::Table)
        return measure_.max_size_depth;
    else return 1;
}

int VarData::columnCount(const QModelIndex &parent) const{
    if(mode_|MODE_REPRESENTATION::Sequential)
        return measure_.total_childs;
    return data_->variables().size();
}

void VarData::set_representable_variable(VariableBase* var){
    var_ = var;
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
}

void VarData::reset_representable_variable(){
    var_ = nullptr;
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
}

QVariant VarData::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    if(role&(Qt::DisplayRole|Qt::EditRole)){

    }
    else return QVariant();
}

bool VarData::setData(const QModelIndex &index, const QVariant &value, int role){

}
Qt::ItemFlags VarData::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()){
        if(index.data(Qt::EditRole).value<TYPE_VAL>()&(ARRAY|NUMERIC_ARRAY|STRING_ARRAY))
            return flags | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        else
            return flags | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    return flags;
}

bool VarData::hasChildren(const QModelIndex &parent) const{
    if(!parent.isValid())
        return false;
    else
        return
}
bool VarData::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role){

}
bool VarData::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles){

}
}
