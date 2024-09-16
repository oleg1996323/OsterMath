#include "model/nodeview_select.h"
#include "model/nodeview_model.h"

namespace model{
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
    if (command == NoUpdate)
        return;
    if (command&Rows){
        mode_ = ROWS_SELECTION;
    }
    if (command&Columns){
        mode_ = COLUMNS_SELECTION;
    }
    if(selection().size()==1){
        if(!(mode_&ROWS_SELECTION) & !(mode_&COLUMNS_SELECTION)){
            if(selection().indexes().size()!=1)
                mode_=ModeSelection::RANGE_SELECTION|mode_;
            else mode_=ModeSelection::SINGLE_SELECTION|mode_;
        }
    }
    else if(selection().size()==0)
        mode_=ModeSelection::NONE;
    else mode_=ModeSelection::CUSTOM_SELECTION;

    if(!sel.indexes().isEmpty())
        setCurrentIndex(sel.indexes().front(),NoUpdate);
    else setCurrentIndex(QModelIndex(),NoUpdate);
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
bool NodeViewSelectionModel::is_single() const{
    return mode_==SINGLE_SELECTION;
}

QModelIndex NodeViewSelectionModel::first_index() const{
    if(!is_empty() && mode_^CUSTOM_SELECTION){
        auto sel = selection().indexes();
        return *std::min(sel.cbegin(),sel.cend(),[](auto lhs, auto rhs){
            return lhs->row()<rhs->row() || lhs->column()<rhs->column();
        });
    }
    else return QModelIndex();
}

void NodeViewSelectionModel::next_from_selection(){
    QModelIndexList selectedIndexes = this->selectedIndexes();
    if(!selectedIndexes.isEmpty()){
        if(!is_single()){
            //for some indexes selection
            int currentIndexPosition = selectedIndexes.indexOf(currentIndex());
            int new_pos = (currentIndexPosition + 1) % selectedIndexes.size();
            if(selectedIndexes.size()>new_pos)
                setCurrentIndex(selectedIndexes.at(new_pos),NoUpdate);
            else setCurrentIndex(selectedIndexes.front(),NoUpdate);
        }
        else{
            //for single selection
            model::NodeView* m = qobject_cast<NodeView*>(model());
            INFO_NODE view_node = m->get_node();
            if(view_node.parent && view_node.id>=-1){
                if(view_node.node()){
                    if(view_node.node()->has_child(currentIndex().column())){
                        if(view_node.node()->child(currentIndex().column())->is_array()){
                            //for array type
                            if(currentIndex().row()+1<=view_node.node()->child(currentIndex().column())->childs().size()){
                                setCurrentIndex(currentIndex().sibling(currentIndex().row()+1,currentIndex().column()),ClearAndSelect);
                            }
                            else{
                                setCurrentIndex(currentIndex().sibling(0,currentIndex().column()+1),ClearAndSelect);
                            }
                        }
                        else{
                            //for value type
                            if(currentIndex().row()<=view_node.node()->child(currentIndex().column())->childs().size()){
                                setCurrentIndex(currentIndex().sibling(currentIndex().row()+1,currentIndex().column()),ClearAndSelect);
                            }
                            else{
                                setCurrentIndex(currentIndex().sibling(0,currentIndex().column()+1),ClearAndSelect);
                            }
                        }
                    }
                    else if(currentIndex().column()+1==m->get_columns_cached_count()){
                        setCurrentIndex(currentIndex().sibling(0,0),ClearAndSelect);
                    }
                    else{
                        setCurrentIndex(m->index(0,0,QModelIndex()),ClearAndSelect);
                    }
                }
                else setCurrentIndex(m->index(0,0,QModelIndex()),ClearAndSelect);
            }
            else setCurrentIndex(QModelIndex(),Clear);
        }
    }
    else setCurrentIndex(QModelIndex(),Clear);
}
}
