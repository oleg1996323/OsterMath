#pragma once
#include <unordered_map>
#include "model/def.h"
#include "model/nodeview_model.h"
#include "model/varlist_model.h"
#include "model/nodeview_select.h"

namespace model{

class Manager:public QObject{
Q_OBJECT
public:
    Data* add_data(QObject* parent, BaseData*);
    void erase_data(BaseData*);
    Data* get_data(BaseData*);
    void clear();

private:
    std::unordered_map<BaseData*,Data> data_;
};
}
