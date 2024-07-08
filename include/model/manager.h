#pragma once
#include <unordered_map>
#include "model/def.h"

namespace model{

class Manager:public QObject{

    const Data& add_data(QObject* parent, BaseData*);
    void erase_data(BaseData*);
    const Data& get_data(BaseData*);

private:
    std::unordered_map<size_t,Data> data_;
};

}
