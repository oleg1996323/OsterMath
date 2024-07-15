#include "model/manager.h"
#include "kernel/exception.h"

namespace model{
Data* Manager::add_data(QObject* parent, BaseData* data){
    if(!data_.contains(data)){
        return &data_.emplace(data,Data(parent,data)).first->second;
    }
    else return nullptr;
}
void Manager::erase_data(BaseData* data_ptr){
    if(data_ptr && data_.contains(data_ptr))
        data_.erase(data_ptr);
}
Data* Manager::get_data(BaseData* data_ptr){
    if(data_ptr && data_.contains(data_ptr))
        return &data_.at(data_ptr);
    else return nullptr;
}

void Manager::clear(){
    data_.clear();
}
}
