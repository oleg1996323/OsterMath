#include <numeric>
#include "model/dataviewmodel.h"
#include "types.h"

namespace model{

DataView::DataView(QWidget* parent, Node* node):
    QAbstractItemModel(parent),
    node_(node)
{

}

//int DataView::rowCount(const QModelIndex &parent) const{
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

//int DataView::columnCount(const QModelIndex &parent) const{
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

int DataView::rowCount(const QModelIndex &parent) const{
    auto max = std::max_element(node_->childs().begin(),node_->childs().end(),[](std::shared_ptr<Node>& lhs, std::shared_ptr<Node>& rhs){
        return lhs->childs().size()<rhs->childs().size();
    });
    if(max==node_->childs().end())
        return 1;
    else return (*max)->childs().size();
}

int DataView::columnCount(const QModelIndex &parent) const{
    return node_ -> childs().size();
}

void DataView::set_representable_node(Node* node){
    node_ = node;
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
}

void DataView::reset_representable_node(){
    node_ = nullptr;
    emit dataChanged(createIndex(0,0),createIndex(0,columnCount()));
}

QVariant DataView::data(const QModelIndex &index, int role) const{
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

bool DataView::setData(const QModelIndex &index, const QVariant &value, int role){

}

Qt::ItemFlags DataView::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()){
        if(index.data(Qt::EditRole).value<TYPE_VAL>()&(ARRAY|NUMERIC_ARRAY|STRING_ARRAY))
            return flags | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        else
            return flags | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    return flags;
}

bool DataView::hasChildren(const QModelIndex &parent) const{
    if(!parent.isValid())
        return false;
    else return parent.data(Qt::EditRole).value<Node*>()->has_childs();
}
bool DataView::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role){

}
bool DataView::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles){

}
}
