#pragma once
#include <unordered_map>
#include "model/def.h"
#include "model/nodeview_model.h"
#include "model/varlist_model.h"

namespace model{

class Manager:public QObject{
Q_OBJECT
public:
    const Data& add_data(QObject* parent, BaseData*);
    void erase_data(BaseData*);
    const Data& get_data(BaseData*);
    void clear();

private:
    std::unordered_map<size_t,Data> data_;
};
}
