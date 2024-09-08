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
}
