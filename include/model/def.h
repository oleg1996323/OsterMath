#pragma once
#include <QMetaType>
#include <QObject>
#include "types.h"
#include "arithmetic_types.h"
#include "data.h"

namespace model{
enum class HEADER{
    NAME,
    TYPE,
    VALUE,
    EXPRESSION,
    REMARK
};

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
}

Q_DECLARE_METATYPE(TYPE_VAL)
Q_DECLARE_METATYPE(model::HEADER)
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(Value_t)
Q_DECLARE_METATYPE(Node*)
Q_DECLARE_METATYPE(VariableBase*)
