#pragma once
#include "types.h"
#include "arithmetic_types.h"

namespace model{
enum class HEADER{
    NAME,
    TYPE,
    VALUE,
    EXPRESSION,
    REMARK
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
