#include "utilities/custom_widgets/tool_group.h"

Group::Group(const QString& title,QWidget* parent):QGroupBox(title,parent){
    setAlignment(Qt::AlignmentFlag::AlignHCenter);
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    setAutoFillBackground(true);
    layout_ = new QGridLayout(this);
}

QGridLayout* Group::grid_layout(){
    return layout_;
}
