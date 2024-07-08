#pragma once
#include <QMainWindow>
#include "varlist.h"
#include "modeldataview.h"

class View:public QMainWindow{
    Q_OBJECT
public:
    View(QWidget* parent, BaseData* data):QMainWindow(parent, Qt::Widget|Qt::WindowTitleHint){
        var_list_ = new VarList::DockWidget(this);
        addDockWidget(Qt::LeftDockWidgetArea,var_list_,Qt::Vertical);
        data_view_ = new ModelDataView(parent);
    }

private:
    //widget where var are illustrated
    VarList::DockWidget* var_list_;
    ModelDataView* data_view_;
};
