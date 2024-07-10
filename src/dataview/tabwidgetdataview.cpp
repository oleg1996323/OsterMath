#include "dataview/tabwidgetdataview.h"
#include <QWidget>
#include "data.h"
#include "dataview/variable_list/dock.h"
#include "dataview/model_data/nodedataview.h"

namespace dataview{

View::View(QWidget* parent, BaseData* data):QMainWindow(parent, Qt::Widget|Qt::WindowTitleHint){
    data_view_ = new NodeData(parent);
    setCentralWidget(data_view_);
}

void View::show_variable_list(){
    if(!var_list_->isVisible()){
        var_list_->show();
    }
}

QAbstractProxyModel* View::search_var(const QString&){

}
}
