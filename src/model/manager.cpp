#include "model/manager.h"

namespace model{
const Data& Manager::add_data(QObject* parent, BaseData* data){
    static Data data_loc = Data(nullptr,nullptr);
    if(data_.contains((size_t)data)){
        return data_.emplace((size_t)data,Data(parent,data)).first->second;
    }
    else return data_loc;
}
void Manager::erase_data(BaseData* data_ptr){
    if(data_ptr && data_.contains((size_t)data_ptr))
        data_.erase((size_t)data_ptr);
}
const Data& Manager::get_data(BaseData* data_ptr){
    static Data data_loc = Data(nullptr,nullptr);
    if(data_ptr && data_.contains((size_t)data_ptr))
        return data_.at((size_t)data_ptr);
    else return data_loc;
}

void Manager::clear(){
    data_.clear();
}
}
