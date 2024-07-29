#include "dataview/expr_view_splitter.h"

namespace dataview{

DataViewSplit::DataViewSplit(QWidget* parent):
    QSplitter(Qt::Vertical,parent),
    ObjectFromSettings(this){
    setObjectName("MainDataView");
    __define_view__();
}

void DataViewSplit::__define_view__(){
    expression_view_ = new VarExpressionView(this);
    sheets_ = new Sheets(this);
    addWidget(expression_view_);
    addWidget(sheets_);
    setCollapsible(0,false);
    setCollapsible(1,false);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setSizes({20,sheets_->maximumHeight()});
}

Sheets* DataViewSplit::sheets() const{
    return sheets_;
}

void DataViewSplit::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
}
void DataViewSplit::__save_settings__(){

}
void DataViewSplit::__upload_fonts__(){

}
void DataViewSplit::__upload_style__(){

}
void DataViewSplit::__upload_language__(){

}
}
