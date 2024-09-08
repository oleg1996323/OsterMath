#include "model/nodeview_select.h"

namespace model{
//void NodeViewSelectionModel::select(const QModelIndex &index, QItemSelectionModel::SelectionFlags command){
//    return;
//}

NodeViewSelectionModel::ModeSelection operator|(NodeViewSelectionModel::ModeSelection lhs, NodeViewSelectionModel::ModeSelection rhs){
    return static_cast<NodeViewSelectionModel::ModeSelection>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

NodeViewSelectionModel::ModeSelection operator&(NodeViewSelectionModel::ModeSelection lhs, NodeViewSelectionModel::ModeSelection rhs){
    return static_cast<NodeViewSelectionModel::ModeSelection>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
}

NodeViewSelectionModel::ModeSelection operator^(NodeViewSelectionModel::ModeSelection lhs, NodeViewSelectionModel::ModeSelection rhs){
    return static_cast<NodeViewSelectionModel::ModeSelection>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs));
}

void NodeViewSelectionModel::select(const QItemSelection &sel, QItemSelectionModel::SelectionFlags command){
    QItemSelectionModel::select(sel,command);

    for(auto i:selection()){
        qDebug()<<i;
    }

    if (command == NoUpdate)
        return;

    if (command&Rows){
        mode_ = ROWS_SELECTION;
    }
    if (command&Columns){
        mode_ = COLUMNS_SELECTION;
    }
    if(selection().size()==1){
        if(!(mode_&ROWS_SELECTION) & !(mode_&COLUMNS_SELECTION))
            mode_=ModeSelection::RANGE_SELECTION|mode_;
    }
    else if(selection().size()==0)
        mode_=ModeSelection::NONE;
    else mode_=ModeSelection::CUSTOM_SELECTION;
}

bool NodeViewSelectionModel::is_columns() const{
    return mode_&COLUMNS_SELECTION;
}
bool NodeViewSelectionModel::is_rows() const{
    return mode_&ROWS_SELECTION;
}
bool NodeViewSelectionModel::is_range() const{
    return mode_&RANGE_SELECTION;
}
bool NodeViewSelectionModel::is_empty() const{
    return mode_==NONE;
}

QModelIndex NodeViewSelectionModel::first_index() const{
    if(!is_empty() && mode_^CUSTOM_SELECTION){
        auto sel = selection().indexes();
        return *std::min(sel.cbegin(),sel.cend(),[](auto lhs, auto rhs){
            qDebug()<<lhs;
            qDebug()<<rhs;
            return lhs->row()<rhs->row() || lhs->column()<rhs->column();
        });
    }
    else return QModelIndex();
}
}
