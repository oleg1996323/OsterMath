#include "model/def.h"
#include "model/nodeview_model.h"
#include "model/varlist_model.h"
#include "model/nodeview_select.h"
#include <QtDebug>

namespace model{

Data::Data(QObject* parent, BaseData* data):
    data_model(std::make_unique<::model::NodeView>(parent)),
    var_model(std::make_unique<::model::Variables>(parent,data)),
    selection_model(std::make_unique<::model::NodeViewSelectionModel>(data_model.get())){}

exceptions::EXCEPTION_TYPE parse_to_insert_item(QString expr, const std::vector<INFO_NODE>& sequence_ID){
    if(sequence_ID.empty())
        return exceptions::NODE_DONT_EXISTS;
    if(!expr.isEmpty() && expr[0]!='=')
        expr="="+expr;
    else if(expr.isEmpty())
        expr = "=";
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
Node* __convert_value_to_array__(Node* parent,int id, size_t sz, bool before){
    if(parent && id!=-1 && parent->has_child(id)){
        std::shared_ptr<Node> new_node = std::make_shared<ArrayNode>(sz);
        parent->child(id)->parents().erase(parent);
        if(!before){
            new_node->insert_back(parent->child(id));
            for(size_t i = 1; i<sz;++i)
                new_node->insert_back(std::make_shared<Node>());
        }
        else{
            for(size_t i = 1; i<sz;++i)
                new_node->insert_back(std::make_shared<Node>());
            new_node->insert_back(std::make_shared<Node>());
        }
        parent->replace(id,new_node);
        return parent->child(id).get();
    }
    else return nullptr;
}
INFO_NODE get_child_node(INFO_NODE from, int child_node_id){ //not QModelIndex for simplification of function
    if(!from.parent || from.id<0)
        return INFO_NODE();
    std::shared_ptr<Node> node = from.node();
    if(node){
        //case when child exists
        if(node->type()==NODE_TYPE::ARRAY){
            if(!node->has_childs()){
                return {from.parent,from.id};
            }
            else{
                if(node->has_child(child_node_id) || child_node_id==node->childs().size())
                    return {node.get(),child_node_id};
                else
                    return INFO_NODE();
            }
        }
        else if(node->type()==NODE_TYPE::VALUE){
            if(child_node_id==0 || child_node_id==1)
                return {from.parent,from.id};
            else return INFO_NODE();
        }
        else if(node->type()==NODE_TYPE::VARIABLE){
            if(child_node_id==0){
                return {from.parent,from.id};
            }
            else return INFO_NODE();
        }
        else{
            if(node->has_child(child_node_id) || child_node_id==node->childs().size())
                return {node.get(),child_node_id};
            else
                return INFO_NODE();
        }
    }
    else{
        return INFO_NODE({from.parent,0});
    }
    return INFO_NODE();
}
}
