#pragma once
#include <QTableView>
#include "model/dataview_delegate.h"
#include "model/data_view_header.h"

namespace dataview{

class NodeData: public QTableView{
    Q_OBJECT
public:
    NodeData(QWidget* parent):QTableView(parent){

    }

private:
    model::DataViewDelegate* delegate_;
    model::DataViewHeader* header_;
};
}
