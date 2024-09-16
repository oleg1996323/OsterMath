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
            std::shared_ptr<Node> node_to_show = sequence_node_.back().node();
            if(!node_to_show){
                cached_row_count_=1;
                return 1;
            }
            if(mode_==MODE_REPRESENTATION::Table){
                auto max = std::max_element(node_to_show->childs().begin(),node_to_show->childs().end(),[](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs){
                    return lhs->childs().size()<rhs->childs().size();
                });
                if(max==node_to_show->childs().end()){
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
            else if(mode_==MODE_REPRESENTATION::Sequential){
                //TODO
                qFatal("Not available in this OsterMath version");
                throw std::runtime_error("Not available in this OsterMath version");
                cached_row_count_ = 1;
            }
            else{
                qFatal("Unknown format representation");
                throw std::runtime_error("Unknown format representation");
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
            std::shared_ptr<Node> node_to_show = sequence_node_.back().node();
            if(!node_to_show){
                cached_column_count_=1;
                return cached_column_count_;
            }
            else
                cached_column_count_ = node_to_show->childs().size()+1;
        }
        else cached_column_count_ = 1;
    }
    return cached_column_count_;
}

void NodeView::set_representable_variable(Node* parent, int id_child){
    beginResetModel();
    sequence_node_.clear();
    sequence_node_.push_back({parent,(int)id_child});
    endResetModel();
}

void NodeView::set_representable_child_node(Node* parent,int id){
    beginResetModel();
    if(sequence_node_.empty())
        return;
    std::shared_ptr<Node> current_node = sequence_node_.back().node();
    if(parent && id>-1)
        sequence_node_.push_back({parent,id});
    endResetModel();
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
            if(sequence_node_.empty())
                return QVariant();

            std::shared_ptr<Node> node_to_show = sequence_node_.back().node();
            if(!node_to_show){
                return QVariant();
            }

            if(node_to_show->is_array()){
                if(node_to_show->has_child(index.column())){
                    if(node_to_show->child(index.column())->is_array()){
                        if(node_to_show->child(index.column())->has_child(index.row())){
                            return QVariant::fromValue(node_to_show->child(index.column())->child(index.row()).get());
                        }
                        else return QVariant();
                    }
                    else{
                        if(index.row()==0)
                            return QVariant::fromValue(node_to_show->child(index.column()).get());
                        else return QVariant();
                    }
                }
                else return QVariant();
            }
            else{
                if(index.column()==0)
                    return QVariant::fromValue(node_to_show.get());
                else return QVariant();
            }
            break;
        }
        default:
            return QVariant();
        }
    }
    else if(mode_==MODE_REPRESENTATION::Sequential){
        //TODO
        qFatal("Not available in this OsterMath version");
        throw std::runtime_error("Not available in this OsterMath version");
    }
    return QVariant();
}

std::vector<INFO_NODE> NodeView::get_sequence_ids_at_set_data(QModelIndex index){
    std::vector<INFO_NODE>::const_iterator begin = last_Variable(sequence_node_);
    if(begin==sequence_node_.end())
        return std::vector<INFO_NODE>();
    std::vector<INFO_NODE> res(begin,sequence_node_.cend());
    if(!res.empty()){
        if(res.back().node()->has_child(index.column())){
            res.push_back({res.back().node().get(),index.column()});
        }
        else if(index.row()==0 && index.column()==cached_column_count_-1){
            if(res.back().node()->is_array())
                res.back().node()->insert_back(std::make_shared<Node>());
            else{
                __convert_value_to_array__(res.back().parent, res.back().id, 2, false);
            }
            res.push_back({res.back().node().get(),index.column()});
            if(index.column()==cached_column_count_-1){
                insertColumn(cached_column_count_,QModelIndex());
                ++cached_column_count_;
            }
            return res;
        }
        else return std::vector<INFO_NODE>();
        if(res.back().node()->is_array()){
            if(res.back().node()->has_child(index.row())){
                res.push_back({res.back().node()->child(index.row()).get(),index.row()});
            }
            else if(index.row()==res.back().node()->childs().size()){
                res.back().node()->insert_back(std::make_shared<Node>());
                res.push_back({res.back().node()->child(index.row()).get(),index.row()});
                if(index.row()==cached_row_count_-1){
                    insertRow(cached_row_count_,QModelIndex());
                    ++cached_row_count_;
                }
                return res;
            }
            else return std::vector<INFO_NODE>();
        }
        else{
            if(index.row()!=0){
                if(index.row()==1){
                    __convert_value_to_array__(res.back().parent, res.back().id, 2, false);
                    res.push_back({res.back().node()->child(index.row()).get(),index.row()});
                    if(index.row()==cached_row_count_-1){
                        insertRow(cached_row_count_,QModelIndex());
                        ++cached_row_count_;
                    }
                }
                else return std::vector<INFO_NODE>();
            }
            else return res;
        }
    }
    else return std::vector<INFO_NODE>();
    return res;
}

bool NodeView::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())
        return false;
    if(mode_==MODE_REPRESENTATION::Table){
        switch((Qt::ItemDataRole)role){
        case(Qt::DisplayRole):
        {
            if(sequence_node_.empty())
                return false;
            std::shared_ptr<Node> node_to_show = sequence_node_.back().node();
            if(!node_to_show){
                return false;
            }
            std::vector<INFO_NODE> arg = get_sequence_ids_at_set_data(index);
            if(arg.empty())
                return false;
            exceptions::EXCEPTION_TYPE err_h = parse_to_insert_item(value.toString(),arg);
            emit dataChanged(createIndex(0,0), createIndex(cached_row_count_-1,cached_column_count_-1));
            return err_h==exceptions::NOEXCEPT;
            break;
        }
        case(Qt::EditRole):{
            setData(index,value,Qt::DisplayRole);
        }
        default:
            return false;
        }
    }
    else if(mode_==MODE_REPRESENTATION::Sequential){
        //TODO another solution for setting (future)
        qFatal("Not available in this OsterMath version");
        throw std::runtime_error("Not available in this OsterMath version");
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
    else if(mode_==MODE_REPRESENTATION::Sequential){
        //TODO
        qFatal("Not available in this OsterMath version");
        throw std::runtime_error("Not available in this OsterMath version");
    }
    else return QVariant();
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
        std::shared_ptr<Node> node_to_show;
        node_to_show = sequence_node_.back().node();

        if(node_to_show->childs().size()!=0){
            beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
            for(auto child_iter = node_to_show->childs().begin();child_iter!=node_to_show->childs().end();++child_iter){
                if((*child_iter)){
                    if(!(*child_iter)->is_array()){
                        if(nRow==0)
                            __convert_value_to_array__(node_to_show.get(),child_iter-node_to_show->childs().begin(),nCount+1,true);
                        else if(nRow==1)
                            __convert_value_to_array__(node_to_show.get(),child_iter-node_to_show->childs().begin(),nCount+1,false);
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
        std::shared_ptr<Node> node_to_show = sequence_node_.back().node();

        beginInsertColumns(QModelIndex(),nCol,nCol+nCount-1);
        if(!node_to_show->is_array()){
            __convert_value_to_array__(sequence_node_.back().parent,sequence_node_.back().id,nCount+1,true);
        }
        else{
            if(nCol<cached_column_count_-1)
                node_to_show->insert(nCol,std::make_shared<Node>());
            else if(nCol==cached_column_count_-1)
                node_to_show->insert_back(std::make_shared<Node>());
            else return false;
        }
        ++cached_column_count_;
        endInsertColumns();
        return true;
    }
    else return false;
}
bool NodeView::insert_row_after(int nRow, int nCount){
    if(!sequence_node_.empty()){
        std::shared_ptr<Node> node_to_show = sequence_node_.back().node();

        if(node_to_show->childs().size()!=0){
            beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);

            for(auto child_iter = node_to_show->childs().begin();child_iter!=node_to_show->childs().end();++child_iter){
                if((*child_iter)){
                    if(!(*child_iter)->is_array()){
                        if(nRow==0){
                            __convert_value_to_array__(node_to_show.get(),child_iter-node_to_show->childs().begin(),nCount+1,false);
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
            return true;
        }
        else return false;
    }
    else return false;
}
bool NodeView::insert_column_after(int nCol, int nCount){
    if(!sequence_node_.empty()){
        std::shared_ptr<Node> node_to_show = sequence_node_.back().node();

        beginInsertColumns(QModelIndex(),nCol,nCol+nCount-1);
        if(!node_to_show->is_array()){
            if(nCol<=cached_column_count_-1)
                __convert_value_to_array__(sequence_node_.back().parent,sequence_node_.back().id,nCount+1,true);
            else return false;
        }
        else{
            node_to_show->insert(nCol+1,std::make_shared<Node>());
        }
        ++cached_column_count_;
        endInsertColumns();
        return true;
    }
    else return false;
}

bool NodeView::removeRows(int nRow, int nCount, const QModelIndex& parent){
    beginRemoveRows(parent,nRow,nRow+nCount-1);
    return true;
    endRemoveRows();
}
bool NodeView::removeColumns(int nCol, int nCount, const QModelIndex& parent){
    beginRemoveColumns(parent,nCol,nCol+nCount-1);
    return true;
    endRemoveColumns();
}

int NodeView::get_rows_cached_count() const{
    return cached_row_count_;
}

int NodeView::get_columns_cached_count() const{
    return cached_column_count_;
}

INFO_NODE NodeView::get_showed_node(QModelIndex index) const{
    INFO_NODE result;
    if(sequence_node_.back().parent->type()==NODE_TYPE::VARIABLE){
        if(sequence_node_.back().parent->has_child(0)){
            if(sequence_node_.back().parent->child(0)->is_array()){
                if(index.column()<sequence_node_.back().parent->child(0)->childs().size()){
                    if(sequence_node_.back().parent->child(0)->child(index.column())->is_array()){
                        if(index.row()<sequence_node_.back().parent->child(0)->child(index.column())->childs().size()){
                            result.parent = sequence_node_.back().parent->child(0)->child(index.column()).get();
                            if(index.row()<result.parent->childs().size())
                                result.id = index.row();
                        }
                    }
                    else{
                        result.parent = sequence_node_.back().parent->child(0).get();
                        if(index.column()<result.parent->childs().size())
                            result.id = index.column();
                    }
                }
            }
            else{
                //if value is assigned to variable
                if(sequence_node_.back().parent->child(0)->has_childs()){
                    assert(sequence_node_.back().parent->child(0)->childs().size()==1);
                    result.parent = sequence_node_.back().parent->child(0).get();
                    if(index.column()==0)
                        result.id = 0;
                }
            }
        }
    }
    else {
        if(sequence_node_.back().parent->is_array()){
            if(index.column()<sequence_node_.back().parent->childs().size()){
                if(sequence_node_.back().parent->child(index.column())->is_array()){
                    if(index.row()<sequence_node_.back().parent->child(index.column())->childs().size()){
                        result.parent = sequence_node_.back().parent->child(index.column()).get();
                        result.id = index.row();
                    }
                }
                else{
                    result.parent = sequence_node_.back().parent;
                    result.id = index.column();
                }
            }
        }
    }
    return result;
}
}
