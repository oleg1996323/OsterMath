#include "utilities/custom_widgets/tool_group.h"
#include <QStylePainter>
#include <QStyleOptionComboBox>

Group::Group(const QString& title,QWidget* parent):QGroupBox(title,parent){
    setAlignment(Qt::AlignmentFlag::AlignHCenter);
    setBackgroundRole(QPalette::Window);
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    layout_ = new QGridLayout(this);
}

QSize Group::sizeHint() const{
    QGridLayout* l = qobject_cast<QGridLayout*>(layout());
    if(l){
        QSize s = QSize(l->columnCount()*l->itemAtPosition(0,0)->widget()->sizeHint().width()+
        contentsMargins().left()+contentsMargins().right()+l->spacing()+
        l->contentsMargins().left()+l->contentsMargins().right(),
        l->rowCount()*l->itemAtPosition(0,0)->widget()->sizeHint().height()+
        contentsMargins().top()+contentsMargins().bottom()+l->spacing()+
        l->contentsMargins().top()+l->contentsMargins().bottom());
        return s;
    }
    else return size();
}

QGridLayout* Group::grid_layout(){
    return layout_;
}

//void Group::paintEvent(QPaintEvent* event){
//    Q_UNUSED(event);
//    QStylePainter p(this);
//    QStyleOptionGroupBox opt;
//    opt.initFrom(this);
//    p.drawPrimitive(QStyle::PE_FrameGroupBox,opt);
//}
