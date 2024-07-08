#include "model/manager.h"
#include "model/varlistmodel.h"
#include "model/dataviewmodel.h"

namespace model{
const Data& Manager::add_data(QObject* parent, BaseData* data){
    static Data data_loc = Data(nullptr,nullptr);
    if(data_.contains((size_t)data)){
        return data_.emplace((size_t)data,Data(parent,data)).first->second;
    }
    else return data_loc;
}
void Manager::erase_data(BaseData*){

}
const Data& Manager::get_data(BaseData*){

}

void show_variable_list();
}
