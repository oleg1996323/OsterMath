#pragma once
#include <QMetaType>
#include <QObject>
#include "types.h"
#include "arithmetic_types.h"
#include "data.h"
#include "exception/exception.h"
#include "kernel/application.h"
#include <QModelIndexList>

namespace model{
enum class HEADER{
    NAME,
    TYPE,
    VALUE,
    EXPRESSION,
    REMARK
};

struct NODE_STRUCT{
    QString expr_;
    QString note_;
    std::shared_ptr<Node> node_;
    TYPE_VAL type_;
    exceptions::EXCEPTION_TYPE err_;
};
//QRegularExpression reg(R"(^[ \t]*VAR\([ \t]*!\(\'[a-zA-Z0-9][^_^\(\)!,;#\' ]+\'\)[ \t]*#[a-zA-Z][a-zA-Z0-9\'\^\*]*[ \t]*\)|[ \t]*#[a-zA-Z][a-zA-Z0-9\'\^\*]*[ \t]*$)");

class NodeView;
class Variables;

class Data{
public:
    Data(QObject* parent, BaseData* data);
    Data(Data&& other) = default;

    std::unique_ptr<::model::NodeView> data_model;
    std::unique_ptr<::model::Variables> var_model;
};

struct ChildsMeasure{
    ChildsMeasure(ChildsMeasure* parent = nullptr):parent_(parent){}

    void update();
    std::vector<ChildsMeasure> childs_;
    ChildsMeasure* parent_;
    size_t size_=0;
    size_t max_size_depth = 0;
    size_t total_childs = 0;
    size_t max_size_last_array = 0;
};

void define_section_subelements(ChildsMeasure& section_sizes, ArrayNode* array);

std::vector<Node*> get_sequential_data(std::vector<Node*>& data,ArrayNode* root);

std::vector<Node*> get_sequential_data(ArrayNode* root);

std::vector<std::vector<Node*>> get_table_data(std::vector<std::vector<Node*>>& data, ArrayNode* root);

std::vector<std::vector<Node*>> get_table_data(ArrayNode* root);

exceptions::EXCEPTION_TYPE parse_to_insert_item(QString expr, const std::vector<INFO_NODE>& sequence_ID);

NODE_STRUCT define_variable(const QString& expr, VariableNode* node);

std::vector<INFO_NODE>::const_iterator last_Variable(const std::vector<INFO_NODE>& sequence);

bool is_row_or_column_selection(const QModelIndexList&);
}

Q_DECLARE_METATYPE(TYPE_VAL)
Q_DECLARE_METATYPE(model::HEADER)
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(Value_t)
Q_DECLARE_METATYPE(Node*)
Q_DECLARE_METATYPE(VariableNode*)
Q_DECLARE_METATYPE(VariableBase*)
Q_DECLARE_METATYPE(Result)
