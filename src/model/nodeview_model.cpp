#include <numeric>
#include "model/nodeview_model.h"
#include "types.h"

namespace model{

NodeView::NodeView(QObject* parent):
    QAbstractTableModel(parent)
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
        cached_row_count_ = 0;
    else{
        if(!sequence_node_.empty()){
            if(mode_==MODE_REPRESENTATION::Table){
                auto max = std::max_element(sequence_node_.back()->childs().begin(),sequence_node_.back()->childs().end(),[](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs){
                    return lhs->childs().size()<rhs->childs().size();
                });
                if(max==sequence_node_.back()->childs().end())
                    cached_row_count_ = 1;
                else if((*max)->childs().size()==0)
                    cached_row_count_ = 2;
                else cached_row_count_ = (*max)->childs().size()+1;
            }
            else{
                cached_row_count_ = 1;
            }
        }
        else cached_row_count_ = 0;
    }
    return cached_row_count_;
}

int NodeView::columnCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;
    else {
        if(!sequence_node_.empty())
            cached_column_count_ = sequence_node_.back()->childs().size()+1;
        else cached_column_count_ = 1;
    }
    return cached_column_count_;
}

void NodeView::set_representable_node(Node* node){
    sequence_node_.clear();
    sequence_node_.push_back(node);
    beginResetModel();
    int rows = rowCount();
    int columns = columnCount();
    //emit dataChanged(createIndex(0,0),createIndex(0,0));
    endResetModel();
}

void NodeView::set_representable_child_node(size_t id){
    if(sequence_node_.back()->has_child(id))
        sequence_node_.push_back(sequence_node_.back()->child(id).get());
}

void NodeView::reset_representable_node(){
    beginResetModel();
    sequence_node_.pop_back();
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
    endResetModel();
}

QVariant NodeView::data(const QModelIndex &index, int role) const{
    if(sequence_node_.empty() || !index.isValid())
        return QVariant();
    if(mode_==MODE_REPRESENTATION::Table){
        switch((Qt::ItemDataRole)role){
        case(Qt::DisplayRole):
            if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE && sequence_node_.back()->has_childs()){
                auto node_to_show = sequence_node_.back()->child(0);
                if(node_to_show->type()==NODE_TYPE::VARIABLE)
                    return QString::fromStdString(reinterpret_cast<VariableNode*>(node_to_show.get())->variable()->name());
                else if(node_to_show->is_array())

            }
            if(sequence_node_.back()->has_child(index.column())){
                auto child = sequence_node_.back()->child(index.column());
                if(child->is_array() && child->has_child(index.row())){
                    if(index.row()+1<child->childs().size()){
                        if(child->child(index.row())->is_array()){
                            return QString("...");
                        }
                        else{
                            std::stringstream stream;
                            sequence_node_.back()->child(index.row())->print_result(stream);
                            return QString::fromStdString(stream.str());
                        }
                    }
                    else return QVariant();
                }
                else if(child->type()==NODE_TYPE::VARIABLE)
                    return QString::fromStdString(reinterpret_cast<VariableNode*>(child.get())->variable()->name());
                else {
                    std::stringstream stream;
                    sequence_node_.back()->print_result(stream);
                    return QString::fromStdString(stream.str());
                }
            }
            break;
        case(Qt::EditRole):
            if(sequence_node_.back()->has_child(index.column())){
                auto child = sequence_node_.back()->child(index.column());
                if(child->is_array() && child->has_child(index.row())){
                    return QVariant::fromValue(child->child(index.row()).get());
                }
                else return QVariant::fromValue(child.get());
            }
            break;
            break;
        default:
            return QVariant();
        }
    }
    else if(mode_==MODE_REPRESENTATION::Sequential){

    }
}

bool NodeView::setData(const QModelIndex &index, const QVariant &value, int role){
    return true;
}

Qt::ItemFlags NodeView::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()){
        return flags | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    return flags;
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
            else return QVariant();
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
    else if(role==Qt::EditRole){
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
    else return QVariant();
}

bool NodeView::insertRows(int nRow, int nCount, const QModelIndex& parent){
    beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);

    endInsertRows();
    return true;
}
bool NodeView::insertColumns(int column, int count, const QModelIndex &parent){
    return true;
}
bool NodeView::removeRows(int nRow, int nCount, const QModelIndex& parent){
    return true;
}
bool NodeView::removeColumns(int nRow, int nCount, const QModelIndex& parent){
    return true;
}

}
