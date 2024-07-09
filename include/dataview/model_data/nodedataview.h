#pragma once
#include <QTableView>
#include "model/nodeview_delegate.h"
#include "model/nodeview_header.h"

namespace dataview{

class NodeData: public QTableView{
    Q_OBJECT
public:
    NodeData(QWidget* parent):QTableView(parent){

    }

private:
    model::NodeViewDelegate* delegate_;
    model::NodeViewHeader* header_;
};
}
