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

    void update(){
        if(parent_){
            if(parent_->max_size_depth<=max_size_depth)
                parent_->max_size_depth=max_size_depth+1;
            parent_->total_childs+=total_childs;
            if(parent_->max_size_last_array<parent_->childs_.size())
                parent_->max_size_last_array = parent_->childs_.size();
        }
    }

    std::vector<ChildsMeasure> childs_;
    ChildsMeasure* parent_;
    size_t size_=0;
    size_t max_size_depth = 0;
    size_t total_childs = 0;
    size_t max_size_last_array = 0;
};

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
            for(auto child:measure.childs_)
        };
    }
    std::vector<std::vector<Node*>> data;
}
}
