#include "model/nodeview_model.h"
#include "model/varlist_model.h"
#include "model/def.h"

namespace model{

Data::Data(QObject* parent, BaseData* data):
    data_model(std::make_unique<::model::NodeView>(parent)),
    var_model(std::make_unique<::model::Variables>(parent,data)){}

void ChildsMeasure::update(){
    if(parent_){
        if(parent_->max_size_depth<=max_size_depth)
            parent_->max_size_depth=max_size_depth+1;
        parent_->total_childs+=total_childs;
        if(parent_->max_size_last_array<parent_->childs_.size())
            parent_->max_size_last_array = parent_->childs_.size();
    }
}

void define_section_subelements(ChildsMeasure& section_sizes, ArrayNode* array){
    if(array->has_childs()){
        section_sizes.size_=array->childs().size();
        for(std::shared_ptr<Node> child:*array){
            if(child->is_array()){
                section_sizes.childs_.push_back(ChildsMeasure(&section_sizes));
                define_section_subelements(section_sizes.childs_.back(), reinterpret_cast<ArrayNode*>(child->execute().get<Node*>()));
                section_sizes.childs_.back().update();
            }
            else {
                std::function<void()> update_max_size_last_array;
                update_max_size_last_array = [&section_sizes, &array](){
                    if(section_sizes.parent_ && section_sizes.parent_->max_size_last_array<section_sizes.parent_->childs_.size()){
                        section_sizes.parent_->max_size_last_array = section_sizes.parent_->childs_.size();
                    }
                };
            }
        }
    }
}

std::vector<Node*> get_sequential_data(std::vector<Node*>& data,ArrayNode* root){
    for(std::shared_ptr<Node>& child:*root)
        if(child->is_array())
            get_sequential_data(data,reinterpret_cast<ArrayNode*>(child->execute().get<Node*>()));
        else data.push_back(child->execute().get<Node*>());
    return data;
}

std::vector<Node*> get_sequential_data(ArrayNode* root){
    ChildsMeasure measure;
    define_section_subelements(measure,root);
    std::vector<Node*> data=[&measure](){std::vector<Node*> res; res.reserve(measure.total_childs); return res;}();
    return get_sequential_data(data,root);
}

std::vector<std::vector<Node*>> get_table_data(std::vector<std::vector<Node*>>& data, ArrayNode* root){

}

std::vector<std::vector<Node*>> get_table_data(ArrayNode* root){
    ChildsMeasure measure;
    define_section_subelements(measure,root);
    {
        std::vector<std::vector<size_t>> vector_sizes;
        std::function<void(std::vector<std::vector<size_t>>&)> def2Dvector;
        def2Dvector = [&def2Dvector,&measure](std::vector<std::vector<size_t>>& vector_sizes){
            for(auto child:measure.childs_){

            }
        };
    }
    std::vector<std::vector<Node*>> data;
}

exceptions::EXCEPTION_TYPE parse_to_insert_item(QString expr, const std::vector<INFO_NODE>& sequence_ID){
    if(sequence_ID.empty())
        return exceptions::NODE_DONT_EXISTS;
    if(!expr.isEmpty() && expr[0]!='=')
        expr="="+expr;
    else expr=expr;
    QString ids;
    {
        bool first = true;
        for(const INFO_NODE& info:sequence_ID){
            if(!first)
                ids+=";";
            else {
                if(info.parent && info.parent->type()==NODE_TYPE::VARIABLE)
                    continue;
                else
                    first=false;
            }
            ids+=QString::number(info.id);
        }
    }
    QString var_full_name;

    if(sequence_ID.begin()->parent && sequence_ID.begin()->parent->type()==NODE_TYPE::VARIABLE){
        VariableNode* var_node = static_cast<VariableNode*>(sequence_ID.begin()->parent);
        var_full_name = QString::fromStdString(var_node->variable()->full_name());
    }
    else return exceptions::VARIABLE_DONT_EXISTS;

    expr = QString(var_full_name+"("+ids+")")+
            expr;
    std::stringstream stream;
    stream<<expr.toStdString();

    kernel::Application::get_active_data()->setstream(stream);
    return exception_handler([&]()->void{
        kernel::Application::get_active_data()->read_new();
    });
}

NODE_STRUCT define_variable(const QString& expr, VariableNode* node){
    NODE_STRUCT var;
    if(!node)
        return var;

    var.node_ = node->variable()->node();
    if(!expr.isEmpty() && expr[0]!='=')
        var.expr_='='+expr;
    else var.expr_=expr;
    std::stringstream stream;
    std::string expr_check = node->variable()->full_name()+var.expr_.toStdString();
    stream<<node->variable()->full_name()<<
            var.expr_.toStdString();

    kernel::Application::get_active_data()->setstream(stream);
    var.err_ = exception_handler([&]()->void{
        kernel::Application::get_active_data()->read_new();
    });
    var.type_ = var.node_->type_val();
    return var;
}

std::vector<INFO_NODE>::const_iterator last_Variable(const std::vector<INFO_NODE>& sequence){
    std::vector<INFO_NODE>::const_iterator begin = sequence.begin();
    for(std::vector<INFO_NODE>::const_iterator info_iter=sequence.end()-1;info_iter>=sequence.begin();--info_iter){
        if(info_iter->parent && info_iter->id!=-1){
            if(info_iter->parent->has_child(info_iter->id) &&
                    info_iter->parent->child(info_iter->id) &&
                    info_iter->parent->child(info_iter->id)->type()==NODE_TYPE::VARIABLE)
                begin = info_iter;
        }
    }
    return begin;
}

bool is_row_or_column_selection(const QModelIndexList& indexes){
    return std::all_of(indexes.begin(),indexes.end(),[&indexes](QModelIndex index){
        return index.row() == indexes.begin()->row() || index.column() == indexes.begin()->column();
    });
}
}
