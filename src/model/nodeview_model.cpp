#include <numeric>
#include "model/nodeview_model.h"
#include "types.h"
#include <QRegularExpression>
#include <QtTest/QAbstractItemModelTester>

namespace model{

NodeView::NodeView(QObject* parent):
    QAbstractTableModel(parent)
{}

int NodeView::rowCount(const QModelIndex &parent) const{
    if(parent.isValid())
        cached_row_count_ = 0;
    else{
        if(!sequence_node_.empty()){
            if(mode_==MODE_REPRESENTATION::Table){
                Node* node_to_show;

                if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
                    if(sequence_node_.back()->has_child(0))
                        node_to_show = sequence_node_.back()->child(0).get();
                    else {
                        cached_row_count_=0;
                        return cached_row_count_;
                    }
                }
                else node_to_show = sequence_node_.back();

                auto max = std::max_element(node_to_show->childs().begin(),node_to_show->childs().end(),[](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs){
                    return lhs->childs().size()<rhs->childs().size();
                });
                if(max==sequence_node_.back()->childs().end())
                    cached_row_count_ = 1;
                else if(*max && (*max)->childs().size()==0)
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
        if(!sequence_node_.empty()){
            Node* node_to_show;

            if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
                if(sequence_node_.back()->has_child(0))
                    node_to_show = sequence_node_.back()->child(0).get();
                else {
                    cached_column_count_=0;
                    return cached_column_count_;
                }
            }
            else node_to_show = sequence_node_.back();
            cached_column_count_ = node_to_show->childs().size()+1;
        }
        else cached_column_count_ = 1;
    }
    return cached_column_count_;
}

void NodeView::set_representable_node(Node* node){

    beginResetModel();
    sequence_node_.clear();
    sequence_node_.push_back(node);
    endResetModel();
}

void NodeView::set_representable_child_node(size_t id){
    if(sequence_node_.back()->has_child(id))
        sequence_node_.push_back(sequence_node_.back()->child(id).get());
}

void NodeView::reset_representable_node(){
    beginResetModel();
    sequence_node_.pop_back();
    endResetModel();
}

QVariant NodeView::data(const QModelIndex &index, int role) const{
    if(sequence_node_.empty() || !index.isValid())
        return QVariant();
    if(mode_==MODE_REPRESENTATION::Table){
        switch((Qt::ItemDataRole)role){
        case(Qt::DisplayRole):
        {
            Node* node_to_show;
            if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
                if(sequence_node_.back()->has_child(0))
                    node_to_show = sequence_node_.back()->child(0).get();
                else return QVariant();
            }
            else {
                if(sequence_node_.back()->has_child(index.column()))
                    node_to_show = sequence_node_.back()->child(index.column()).get();
                else return QVariant();
            }

            if(node_to_show->type()==NODE_TYPE::VARIABLE){
                if(index.row()==0)
                    return QString::fromStdString(reinterpret_cast<VariableNode*>(node_to_show)->variable()->name());
                else return QVariant();
            }
            else if(node_to_show->is_array()){
                if(node_to_show->has_child(index.column())){
                    Node* column_child = node_to_show->child(index.column()).get();
                    if(column_child->type()==NODE_TYPE::VARIABLE){
                        if(index.row()<node_to_show->childs().size())
                            return QString::fromStdString(reinterpret_cast<VariableNode*>(column_child)->variable()->name());
                        else return QVariant();
                    }
                    else if(column_child->is_array()){
                        Node* row_child;
                        if(column_child->has_child(index.row())){
                            row_child = column_child->child(index.row()).get();
                            if(row_child->type()==NODE_TYPE::VARIABLE){
                                if(index.row()<node_to_show->childs().size())
                                    return QString::fromStdString(reinterpret_cast<VariableNode*>(row_child)->variable()->name());
                                else return QVariant();
                            }
                            else if(row_child->is_array())
                                return QString("...");
                            else {
                                std::stringstream stream;
                                row_child->print_result(stream);
                                return QString::fromStdString(stream.str());
                            }
                        }
                    }
                    else{
                        if(index.row()==0){
                            std::stringstream stream;
                            column_child->print_result(stream);
                            return QString::fromStdString(stream.str());
                        }
                        else return QVariant();
                    }
                }
                else return QVariant();
            }
            else {
                if(index.row()==0){
                    std::stringstream stream;
                    node_to_show->print_result(stream);
                    return QString::fromStdString(stream.str());
                }
                else return QVariant();
            }
            break;
        }
        case(Qt::EditRole):
        {
            Node* node_to_show;

            if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
                if(sequence_node_.back()->has_child(0))
                    node_to_show = sequence_node_.back()->child(0).get();
                else return QVariant();
            }
            else {
                if(sequence_node_.back()->has_child(index.column()))
                    node_to_show = sequence_node_.back()->child(index.column()).get();
                else return QVariant();
            }

            if(node_to_show->type()==NODE_TYPE::VARIABLE){
                if(index.row()==0)
                    return QVariant::fromValue(node_to_show);
                else return QVariant();
            }
            else if(node_to_show->is_array()){
                if(node_to_show->has_child(index.column())){
                    Node* column_child = node_to_show->child(index.column()).get();
                    if(column_child->type()==NODE_TYPE::VARIABLE)
                        return QVariant::fromValue(column_child);
                    else if(column_child->is_array()){
                        if(column_child->has_child(index.row()))
                            return QVariant::fromValue(column_child->child(index.row()).get());
                        else return QVariant();
                    }
                    else{
                        if(index.row()==0)
                            return QVariant::fromValue(column_child);
                        else return QVariant();
                    }
                }
                else return QVariant();
            }
            else {
                if(index.row()==0)
                    return QVariant::fromValue(node_to_show);
                else return QVariant();
            }
            break;
        }
        default:
            return QVariant();
        }
    }
    else if(mode_==MODE_REPRESENTATION::Sequential){

    }
    return QVariant();
}

//TODO
bool NodeView::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())
        return false;
    if(mode_==MODE_REPRESENTATION::Table){
        switch((Qt::ItemDataRole)role){
        case(Qt::DisplayRole):
        {
            std::shared_ptr<Node>& node_to_show = get_showed_node(index);

            NODE_STRUCT res = parse_to_insert_item(value.toString());
            bool success = true;
            success = res.err_==exceptions::EXCEPTION_TYPE::NOEXCEPT?true:false;
            if(res.node_->has_child(0)){
                node_to_show.swap(res.node_->child(0));
            }
            emit dataChanged(createIndex(0,0), createIndex(rowCount(),0));
            return success;
            break;
        }
        case(Qt::EditRole):
        {
            Node* node_to_show;

            if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
                if(sequence_node_.back()->has_child(0))
                    node_to_show = sequence_node_.back()->child(0).get();
                else return false;
            }
            else {
                if(sequence_node_.back()->has_child(index.column()))
                    node_to_show = sequence_node_.back()->child(index.column()).get();
                else return false;
            }

            if(node_to_show->type()==NODE_TYPE::VARIABLE){
                if(index.row()==0 && value.canConvert<Node*>()){
                    //set pointer to node QVariant::fromValue(node_to_show);
                    return true;
                }
                else return false;
            }
            else if(node_to_show->is_array()){
                if(node_to_show->has_child(index.column())){
                    Node* column_child = node_to_show->child(index.column()).get();
                    if(column_child->type()==NODE_TYPE::VARIABLE){
                        //set pointer to node QVariant::fromValue(column_child);
                        return true;
                    }
                    else if(column_child->is_array()){
                        if(column_child->has_child(index.row())){
                            //set pointer to node QVariant::fromValue(column_child->child(index.row()).get());
                            return true;
                        }
                        else return false;
                    }
                    else{
                        if(index.row()==0){
                            //set pointer to node QVariant::fromValue(column_child);
                            return true;
                        }
                        else return false;
                    }
                }
                else return false;
            }
            else {
                if(index.row()==0){
                    //set pointer to node QVariant::fromValue(node_to_show);
                    return true;
                }
                else return false;
            }
            break;
        }
        default:
            return false;
        }
    }
    else if(mode_==MODE_REPRESENTATION::Sequential){
        //another solution for setting (future)
    }
    return false;
}

Qt::ItemFlags NodeView::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()){
        return (index.isValid())?flags | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable:flags;
    }
    return flags;
}

QVariant NodeView::headerData(int section, Qt::Orientation orientation, int role) const{
    if(sequence_node_.empty())
        return QVariant();
    if(mode_==MODE_REPRESENTATION::Table){
        switch((Qt::ItemDataRole)role){
        case(Qt::DisplayRole):
        {
            return section+1;
        }
        case(Qt::EditRole):
        {
            return section+1;
        }
        default:
            return QVariant();
        }
    }
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

std::shared_ptr<Node>& NodeView::get_showed_node(QModelIndex index) const{
    static std::shared_ptr<Node> no_result;
    if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
        if(sequence_node_.back()->has_child(0)){
            if(sequence_node_.back()->child(0)->is_array()){
                if(index.column()<sequence_node_.back()->child(0)->childs().size()){
                    if(sequence_node_.back()->child(0)->child(index.column())->is_array()){
                        if(index.row()<sequence_node_.back()->child(0)->child(index.column())->childs().size())
                            return sequence_node_.back()->child(0)->child(index.column())->child(index.row());
                        else return no_result;
                    }
                    else{
                        std::shared_ptr<Node>& res = sequence_node_.back()->child(0)->child(index.column());
                        return res;
                    }
                }
                else return no_result;
            }
        }
        else return no_result;
    }
    else {
        if(sequence_node_.back()->is_array()){
            if(index.column()<sequence_node_.back()->childs().size()){
                    if(sequence_node_.back()->child(index.column())->is_array()){
                        if(index.row()<sequence_node_.back()->child(index.column())->childs().size())
                            return sequence_node_.back()->child(index.column())->child(index.row());
                        else return no_result;
                    }
                    else{
                        return sequence_node_.back()->child(index.column());
                    }
                }
                else return no_result;
        }
        else return no_result;
    }
    return no_result;
}
}
