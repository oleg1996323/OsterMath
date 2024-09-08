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
class NodeViewSelectionModel;

class Data{
public:
    Data(QObject* parent, BaseData* data);
    Data(Data&&) = default;

    std::unique_ptr<::model::NodeView> data_model;
    std::unique_ptr<::model::Variables> var_model;
    std::unique_ptr<::model::NodeViewSelectionModel> selection_model;
};
exceptions::EXCEPTION_TYPE parse_to_insert_item(QString expr, const std::vector<INFO_NODE>& sequence_ID);
NODE_STRUCT define_variable(const QString& expr, VariableNode* node);
std::vector<INFO_NODE>::const_iterator last_Variable(const std::vector<INFO_NODE>& sequence);
}

Q_DECLARE_METATYPE(TYPE_VAL)
Q_DECLARE_METATYPE(model::HEADER)
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(Value_t)
Q_DECLARE_METATYPE(Node*)
Q_DECLARE_METATYPE(VariableNode*)
Q_DECLARE_METATYPE(VariableBase*)
Q_DECLARE_METATYPE(Result)
