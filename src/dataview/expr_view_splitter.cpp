#include "dataview/expr_view_splitter.h"

namespace dataview{

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
}
