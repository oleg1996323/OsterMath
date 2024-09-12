#include "utilities/custom_widgets/tabbed_toolbox_group.h"
#include <QVariant>

TabbedGroupedTools::TabbedGroupedTools(QWidget* parent, Qt::Orientation o):
    QTabWidget(parent), orientation_(o){
    setContentsMargins(0,0,0,0);
    setTabPosition(o&Qt::Horizontal?QTabWidget::North:QTabWidget::West);
}

void TabbedGroupedTools::set_box(QList<QGroupBox*> tools, QString name, int id){
    QWidget* widget = new QWidget(this);
    QBoxLayout* layout;
    if(orientation_==Qt::Horizontal)
        layout = new QBoxLayout(QBoxLayout::LeftToRight,widget);
    else layout = new QBoxLayout(QBoxLayout::TopToBottom,widget);
    for(auto box:tools){
        layout->addWidget(box);
        layout->setAlignment(box,Qt::AlignLeft|Qt::AlignVCenter);
        boxes_.append(box);
    }
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addStretch();
    widget->setLayout(layout);
    if(id<0)
        addTab(widget,name);
    else insertTab(id,widget,name);
}

void TabbedGroupedTools::setGroupsMargins(int left,int top,int right,int bottom){
    for(auto box:boxes_){
        if(box)
            box->setContentsMargins(left,top,right,bottom);
    }
}

void TabbedGroupedTools::setGroupsMargins(QMargins margins){
    setGroupsMargins(margins.left(),margins.top(),margins.right(),margins.bottom());
}

void TabbedGroupedTools::setLayoutsContentsMargins(int left,int top,int right,int bottom){
    for(int i = 0;i<count();++i){
        QWidget* w = widget(i);
        if(w)
            w->layout()->setContentsMargins(left,top,right,bottom);
    }
}

void TabbedGroupedTools::setLayoutsContentsMargins(QMargins margins){
    setLayoutsContentsMargins(margins.left(),margins.top(),margins.right(),margins.bottom());
}
