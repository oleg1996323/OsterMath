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
                        id_max_row_childs_ = -1;
                        return cached_row_count_;
                    }
                }
                else node_to_show = sequence_node_.back();

                auto max = std::max_element(node_to_show->childs().begin(),node_to_show->childs().end(),[](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs){
                    return lhs->childs().size()<rhs->childs().size();
                });
                if(max==sequence_node_.back()->childs().end()){
                    cached_row_count_ = 1;
                    id_max_row_childs_ = -1;
                }
                else{
                    if((*max)){
                        if((*max)->childs().size()==0){
                            cached_row_count_ = 2;
                            id_max_row_childs_ = -1;
                        }
                        else{
                            cached_row_count_ = (*max)->childs().size()+1;
                            id_max_row_childs_ = max - node_to_show->childs().begin();
                        }
                    }
                    else{
                        cached_row_count_ = 0;
                        id_max_row_childs_ = -1;
                        return 0;
                    }
                }
            }
            else{
                //if sequential representation TODO further
                cached_row_count_ = 1;
            }
        }
        else {
            cached_row_count_ = 0;
            id_max_row_childs_ = -1;
        }
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
            Node* node_to_show = data(index,Qt::EditRole).value<Node*>();
            if(!node_to_show)
                return QVariant();

            if(node_to_show->type()==NODE_TYPE::VARIABLE){
                if(index.row()==0)
                    return QString::fromStdString(reinterpret_cast<VariableNode*>(node_to_show)->variable()->name());
                else return QVariant();
            }
            else if(node_to_show->is_array()){
                return QString("...");
            }
            else {
                if(index.row()+1<cached_row_count_){
                    std::stringstream stream;
                    node_to_show->print_result(stream);
                    return QString::fromStdString(stream.str());
                }
            }
            break;
        }
        case(Qt::EditRole):
        {
            Node* node_to_show;

            if(sequence_node_.empty())
                return QVariant();

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
        //next version TODO
    }
    return QVariant();
}

//TODO optimize code
bool NodeView::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())
        return false;
    if(mode_==MODE_REPRESENTATION::Table){
        switch((Qt::ItemDataRole)role){
        case(Qt::DisplayRole):
        {
            NODE_STRUCT res = parse_to_insert_item(value.toString()); //value
            bool success = true;
            success = res.err_==exceptions::EXCEPTION_TYPE::NOEXCEPT?true:false;
            if(res.node_){
                Node* node_to_show;

                if(sequence_node_.empty())
                    return false;

                if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
                    if(sequence_node_.back()->has_child(0))
                        node_to_show = sequence_node_.back()->child(0).get();
                    else return false;
                }
                else {
                    node_to_show = sequence_node_.back();
                }

                if(node_to_show->is_array()){
                    if(index.column()<node_to_show->childs().size()){
                        assert(node_to_show->has_child(index.column()));
                        if(index.row()==0){
                            std::shared_ptr<Node> res_node = node_to_show->child(index.column())->replace(index.column(),res.node_);
                            if(res_node)
                                res_node->parents().erase(node_to_show);
                        }
                        else{
                            if(node_to_show->child(index.column())->is_array()){
                                if(index.row()<node_to_show->child(index.column())->childs().size()){
                                    std::shared_ptr<Node> res_node = node_to_show->child(index.column())->replace(index.row(),res.node_);
                                    if(res_node)
                                        res_node->parents().erase(node_to_show->child(index.column()).get());
                                }
                                else{
                                    node_to_show->child(index.column())->insert_back(res.node_);
                                    if(node_to_show->child(index.column())->childs().size()==cached_row_count_){
                                        insertRows(cached_row_count_,1,QModelIndex());
                                        id_max_row_childs_ = index.column();
                                    }
                                }
                            }
                            else{
                                std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(2);
                                node_to_show->child(index.column())->parents().erase(node_to_show);
                                new_node->insert_back(node_to_show->child(index.column()));
                                new_node->insert_back(res.node_);
                                node_to_show->replace(index.column(),new_node);
                                if(new_node->childs().size()==cached_row_count_){
                                    insertRows(cached_row_count_,1,QModelIndex());
                                    id_max_row_childs_ = index.column();
                                }
                            }
                        }
                    }
                    else{
                        node_to_show->insert_back(res.node_);
                        if(node_to_show->childs().size()==cached_column_count_){
                            insertColumns(cached_column_count_,1,QModelIndex());
                        }
                    }
                }
                else{
                    std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(2);
                    node_to_show->child(index.column())->parents().erase(node_to_show);
                    new_node->insert_back(node_to_show->child(index.column()));
                    new_node->insert_back(res.node_);
                    node_to_show->replace(0,new_node);
                    if(new_node->childs().size()==cached_column_count_){
                        insertColumns(cached_column_count_,1,QModelIndex());
                    }
                }
            }
            emit dataChanged(createIndex(0,0), createIndex(cached_row_count_-1,cached_column_count_-1));
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
    if(nRow==cached_row_count_){
        beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
        endInsertRows();
    }
    return true;
}
bool NodeView::insertColumns(int nCol, int nCount, const QModelIndex &parent){
    if(nCol==cached_column_count_){
        beginInsertColumns(QModelIndex(),nCol,nCol+nCount-1);
        endInsertColumns();
        return true;
    }
    return true;
}

bool NodeView::insert_row_before(int nRow, int nCount){
    if(!sequence_node_.empty()){
        Node* node_to_show;
        if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
            if(sequence_node_.back()->has_child(0))
                node_to_show = sequence_node_.back()->child(0).get();
            else return false;
        }
        else node_to_show = sequence_node_.back();

        if(node_to_show->childs().size()!=0){
            beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
            for(auto child_iter = node_to_show->childs().begin();child_iter!=node_to_show->childs().end();++child_iter){
                if((*child_iter)){
                    if(!(*child_iter)->is_array()){
                        std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(2);
                        node_to_show->child(child_iter-node_to_show->childs().begin())->parents().erase(node_to_show);
                        if(nRow==0){
                            new_node->insert_back(std::make_shared<Node>());
                            new_node->insert_back(node_to_show->child(child_iter-node_to_show->childs().begin()));
                        }
                        else if(nRow==1){
                            new_node->insert_back(node_to_show->child(child_iter-node_to_show->childs().begin()));
                            new_node->insert_back(std::make_shared<Node>());
                        }
                        else{continue;}
                        node_to_show->replace(child_iter-node_to_show->childs().begin(),new_node);
                    }
                    else{
                        if(nRow<(*child_iter)->childs().size()){
                            (*child_iter)->insert(nRow,std::make_shared<Node>());
                        }
                        else if(nRow==(*child_iter)->childs().size())
                            (*child_iter)->insert_back(std::make_shared<Node>());
                        else{continue;}
                    }
                    ++cached_row_count_;
                }
            }
            endInsertRows();
            return true;
        }
        else return false;
    }
    else return false;
}
bool NodeView::insert_column_before(int nCol, int nCount){
    if(!sequence_node_.empty()){
        Node* node_to_show;
        if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
            if(sequence_node_.back()->has_child(0))
                node_to_show = sequence_node_.back()->child(0).get();
            else return false;
        }
        else node_to_show = sequence_node_.back();

        beginInsertColumns(QModelIndex(),nCol,nCol+nCount-1);
        if(!node_to_show->is_array()){
            std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(nCount+1);
            new_node->insert_back(std::make_shared<Node>());
            new_node->insert_back(node_to_show->child(nCol));
            node_to_show->replace(0,new_node);
        }
        else{
            node_to_show->insert(nCol,std::make_shared<Node>());
        }
        ++cached_column_count_;
        endInsertColumns();
        return true;
    }
    else return false;
}
bool NodeView::insert_row_after(int nRow, int nCount){
    if(!sequence_node_.empty()){
        Node* node_to_show;
        if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
            if(sequence_node_.back()->has_child(0))
                node_to_show = sequence_node_.back()->child(0).get();
            else return false;
        }
        else node_to_show = sequence_node_.back();

        if(node_to_show->childs().size()!=0){
            beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);

            for(auto child_iter = node_to_show->childs().begin();child_iter!=node_to_show->childs().end();++child_iter){
                if((*child_iter)){
                    if(!(*child_iter)->is_array()){
                        if(nRow==0){
                            std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(2);
                            node_to_show->child(child_iter-node_to_show->childs().begin())->parents().erase(node_to_show);
                            new_node->insert_back(node_to_show->child(child_iter-node_to_show->childs().begin()));
                            new_node->insert_back(std::make_shared<Node>());
                            node_to_show->replace(child_iter-node_to_show->childs().begin(),new_node);
                        }
                        else continue;
                    }
                    else{
                        if(nRow<(*child_iter)->childs().size()){
                            (*child_iter)->insert(nRow,std::make_shared<Node>());
                        }
                        else if(nRow==(*child_iter)->childs().size())
                            (*child_iter)->insert_back(std::make_shared<Node>());
                        else{continue;}
                    }
                    ++cached_row_count_;
                }
                else return false;
            }
            endInsertRows();
        }
        else return false;
    }
    else return false;
}
bool NodeView::insert_column_after(int nCol, int nCount){
    if(!sequence_node_.empty()){
        Node* node_to_show;
        if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
            if(sequence_node_.back()->has_child(0))
                node_to_show = sequence_node_.back()->child(0).get();
            else return false;
        }
        else node_to_show = sequence_node_.back();

        beginInsertColumns(QModelIndex(),nCol,nCol+nCount-1);
        if(!node_to_show->is_array()){
            std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(nCount+1);
            new_node->insert_back(node_to_show->child(nCol));
            new_node->insert_back(std::make_shared<Node>());
            node_to_show->replace(0,new_node);
        }
        else{
            node_to_show->insert(nCol,std::make_shared<Node>());
        }
        ++cached_column_count_;
        endInsertColumns();
        return true;
    }
    else return false;
}

bool NodeView::removeRows(int nRow, int nCount, const QModelIndex& parent){
    return true;
}
bool NodeView::removeColumns(int nRow, int nCount, const QModelIndex& parent){
    return true;
}

int NodeView::get_rows_cached_count() const{
    return cached_row_count_;
}

int NodeView::get_columns_cached_count() const{
    return cached_column_count_;
}

INFO_NODE NodeView::get_showed_node(QModelIndex index) const{
    INFO_NODE result;
    if(sequence_node_.back()->type()==NODE_TYPE::VARIABLE){
        if(sequence_node_.back()->has_child(0)){
            if(sequence_node_.back()->child(0)->is_array()){
                if(index.column()<sequence_node_.back()->child(0)->childs().size()){
                    if(sequence_node_.back()->child(0)->child(index.column())->is_array()){
                        if(index.row()<sequence_node_.back()->child(0)->child(index.column())->childs().size()){
                            result.parent = sequence_node_.back()->child(0)->child(index.column()).get();
                            if(index.row()<result.parent->childs().size())
                                result.id = index.row();
                        }
                    }
                    else{
                        result.parent = sequence_node_.back()->child(0).get();
                        if(index.column()<result.parent->childs().size())
                            result.id = index.column();
                    }
                }
            }
            else{
                //if value is assigned to variable
                if(sequence_node_.back()->child(0)->has_childs()){
                    assert(sequence_node_.back()->child(0)->childs().size()==1);
                    result.parent = sequence_node_.back()->child(0).get();
                    if(index.column()==0)
                        result.id = 0;
                }
            }
        }
    }
    else {
        if(sequence_node_.back()->is_array()){
            if(index.column()<sequence_node_.back()->childs().size()){
                if(sequence_node_.back()->child(index.column())->is_array()){
                    if(index.row()<sequence_node_.back()->child(index.column())->childs().size()){
                        result.parent = sequence_node_.back()->child(index.column()).get();
                        result.id = index.row();
                    }
                }
                else{
                    result.parent = sequence_node_.back();
                    result.id = index.column();
                }
            }
        }
    }
    return result;
}
}
