#include <numeric>
#include "model/nodeview_model.h"
#include "types.h"

namespace model{

NodeView::NodeView(QObject* parent):
    QAbstractItemModel(parent)
{

}

//int NodeView::rowCount(const QModelIndex &parent) const{
//    unsigned long row = 0;
//    switch(mode_){
//    case(MODE_REPRESENTATION::Sequential):{
//        return 1;
//        break;
//    }
//    case(MODE_REPRESENTATION::Table):{
//        std::function<void(const SubNodes&)> recurse = [&row, &recurse](const SubNodes& subnode_loc){
//            if(!subnode_loc.openned_.empty())
//                for(auto child_subnode:subnode_loc.openned_)
//                    recurse(child_subnode);
//            else{
//                row+=subnode_loc.node_->childs().size();
//            }
//        };
//        for(auto subnode:openned_)
//            recurse(subnode);
//        }

//    }
//    return row;
//}

//int NodeView::columnCount(const QModelIndex &parent) const{
//    unsigned long col = 0;
//    switch(mode_){
//    case(MODE_REPRESENTATION::Sequential):{
//        std::function<void(const SubNodes&)> recurse = [&col, &recurse](const SubNodes& subnode_loc){
//            if(subnode_loc.openned_.empty())
//                col+=subnode_loc.node_->childs().size();
//            else
//                for(auto child_subnode:subnode_loc.openned_)
//                    recurse(child_subnode);
//        };
//        for(auto subnode:openned_)
//            recurse(subnode);
//    }
//    case(MODE_REPRESENTATION::Table):{
//        std::function<void(const SubNodes&)> recurse = [&col, &recurse](const SubNodes& subnode_loc){
//            if(!subnode_loc.openned_.empty())
//                for(auto child_subnode:subnode_loc.openned_)
//                    recurse(child_subnode);
//            else{
//                if(subnode_loc.node_->has_parents())
//                    col+=(*subnode_loc.node_->parents().begin())->childs().size();
//            }
//        };
//        for(auto subnode:openned_)
//            recurse(subnode);
//    }
//    }
//    return col;
//}

int NodeView::rowCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;
    else{
        if(!sequence_node_.empty()){
            auto max = std::max_element(sequence_node_.back()->childs().begin(),sequence_node_.back()->childs().end(),[](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs){
                return lhs->childs().size()<rhs->childs().size();
            });
            if(max==sequence_node_.back()->childs().end())
                return 1;
            else return (*max)->childs().size();
        }
        else return 0;
    }
}

int NodeView::columnCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;
    else {
        if(!sequence_node_.empty())
            return sequence_node_.back()->childs().size();
        else return 0;
    }
}

void NodeView::set_representable_node(Node* node){
    sequence_node_.clear();
    sequence_node_.push_back(node);
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
}

void NodeView::set_representable_child_node(size_t id){
    if(sequence_node_.back()->has_child(id))
        sequence_node_.push_back(sequence_node_.back()->child(id).get());
}

void NodeView::reset_representable_node(){
    sequence_node_.pop_back();
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
}

QVariant NodeView::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();

    switch(role){
    case(Qt::DisplayRole):

        break;
    case(Qt::EditRole):

        break;

    default:
        return QVariant();
    }
}

bool NodeView::setData(const QModelIndex &index, const QVariant &value, int role){

}

Qt::ItemFlags NodeView::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()){
        if(index.data(Qt::EditRole).value<TYPE_VAL>()&(ARRAY|NUMERIC_ARRAY|STRING_ARRAY))
            return flags | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        else
            return flags | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    return flags;
}

bool NodeView::hasChildren(const QModelIndex &parent) const{
    if(!parent.isValid())
        return false;
    else return parent.data(Qt::EditRole).value<Node*>()->has_childs();
}
bool NodeView::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role){

}
QVariant NodeView::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole){
        if(mode_==MODE_REPRESENTATION::Table){
            if(sequence_node_.size()>1){
                if(orientation&Qt::Horizontal){
                    Node* node = sequence_node_.at(sequence_node_.size()-2)->child(section).get();
                    if(node->type()==NODE_TYPE::VARIABLE)
                        return QVariant::fromValue(reinterpret_cast<VariableNode*>(node)->variable()->name());
                    else return section;
                }
                else{
                    Node* node = sequence_node_.back()->child(section).get();
                    if(node->type()==NODE_TYPE::VARIABLE)
                        return QVariant::fromValue(reinterpret_cast<VariableNode*>(node)->variable()->name());
                    else return section;

                }
            }
            else return 0;
        }
        else if(mode_==MODE_REPRESENTATION::Sequential){
            if(!sequence_node_.empty()){
                if(orientation&Qt::Horizontal){
                    Node* node = sequence_node_.at(sequence_node_.size()-2)->child(section).get();
                    if(node->type()==NODE_TYPE::VARIABLE)
                        return QVariant::fromValue(reinterpret_cast<VariableNode*>(node)->variable()->name());
                    else return section;
                }
                else{
                    Node* node = sequence_node_.back()->child(section).get();
                    if(node->type()==NODE_TYPE::VARIABLE)
                        return QVariant::fromValue(reinterpret_cast<VariableNode*>(node)->variable()->name());
                    else return section;
                }
            }
            else return 0;
        }
        else throw std::runtime_error("Internal error. Prompt: undefined mode-representation.");
    }
    else {

    }
}
bool NodeView::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles){

}

QModelIndex NodeView::index(int row, int column, const QModelIndex &parent) const{
    if(row>0 && column>0){
        Node* parent_node = static_cast<Node*>(parent.internalPointer());
        if(parent_node){
            if(mode_&MODE_REPRESENTATION::Sequential){
                if(parent_node->has_child(column))
                    return createIndex(1,column,parent_node->child(column).get());
                else
                    return QModelIndex();
            }
            else{
                if(parent_node->has_child(column) && parent_node->child(column)->has_child(row))
                    return createIndex(row,column,parent_node->child(column)->child(row).get());
                else return QModelIndex();
            }
        }
        else{
            return QModelIndex();
        }
    }
}

QModelIndex NodeView::parent(const QModelIndex &child) const{
    Node* child_node = static_cast<Node*>(child.internalPointer());
    if(child_node && child_node->has_parents()){
        Node* parent = (*child_node->parents().begin());
        return createIndex(0,0,parent);
    }
    else return QModelIndex();
}

}
