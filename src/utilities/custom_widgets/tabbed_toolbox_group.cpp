#include "utilities/custom_widgets/tabbed_toolbox_group.h"
#include <QVariant>

TabbedGroupedTools::TabbedGroupedTools(QWidget* parent, Qt::Orientation o):QTabWidget(parent){
    setContentsMargins(0,0,0,0);
    setTabPosition(o&Qt::Horizontal?QTabWidget::North:QTabWidget::West);
}

void TabbedGroupedTools::set_box(QList<QGroupBox*> tools, QString name, int id){
    QWidget* widget = new QWidget(this);
    QBoxLayout* layout = new QBoxLayout(orientation_&Qt::Horizontal?QBoxLayout::LeftToRight:QBoxLayout::TopToBottom,widget);
    for(auto box:tools){
        layout->addWidget(box);
        layout->setMargin(0);
    }
    layout->addSpacing(100);
    widget->setLayout(layout);
    if(id<0)
        addTab(widget,name);
    else insertTab(id,widget,name);
}

void TabbedGroupedTools::setGroupsMargins(int left,int top,int right,int bottom){
    for(auto box:boxes_){
        box->setContentsMargins(left,top,right,bottom);
    }
}

void TabbedGroupedTools::setGroupsMargins(QMargins margins){
    for(auto box:boxes_){
        box->setContentsMargins(margins);
    }
}

void TabbedGroupedTools::setLayoutsContentsMargins(int margin){
    for(int i = 0;i<count();++i){
        QWidget* w = widget(i);
        if(w)
            w->layout()->setMargin(margin);
    }
}
