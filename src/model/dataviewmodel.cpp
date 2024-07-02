#include "model/dataviewmodel.h"
#include "types.h"

namespace model{

VarData::VarData(QWidget* parent, VariableBase* var):
    QAbstractTableModel(parent),
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
}
