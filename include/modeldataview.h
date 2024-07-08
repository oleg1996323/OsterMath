#pragma once
#include <QTableView>
#include "model/dataview_delegate.h"
#include "model/data_view_header.h"

class ModelDataView: public QTableView{
    Q_OBJECT
public:
    ModelDataView(QWidget* parent):QTableView(parent){

    }

private:
    model::DataViewDelegate* delegate_;
    model::DataViewHeader* header_;
};
