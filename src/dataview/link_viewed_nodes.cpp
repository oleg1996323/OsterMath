#include "dataview/link_viewed_nodes.h"
#include "arithmetic_types.h"
#include "kernel/application.h"
#include <QStylePainter>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QFontMetrics>
#include <QMargins>
#include <QSizePolicy>

namespace dataview{

uint8_t LinkViewedNodes::LinkButton::arrowSize = 5 + kernel::settings::Program::get_font_inc();
uint8_t LinkViewedNodes::LinkButton::arrowLenght = 20+2*kernel::settings::Program::get_font_inc();
uint8_t LinkViewedNodes::LinkButton::arrowTextSpacing=arrowSize;
uint8_t LinkViewedNodes::LinkButton::arrowTotalLength(){
    return arrowTextSpacing+arrowLenght+arrowSize;
}

void LinkViewedNodes::__retranslate__(){

}
void LinkViewedNodes::__upload_language__(){

}
void LinkViewedNodes::__upload_fonts__(){

}
void LinkViewedNodes::__upload_style__(){

}
void LinkViewedNodes::__load_settings__(){}
void LinkViewedNodes::__save_settings__(){}

LinkViewedNodes::LinkButton::LinkButton(QString text,QWidget* parent,int32_t pos):PushLabel(text,parent),pos_(pos){
    setContentsMargins(0,0,0,0);
    QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Preferred,QSizePolicy::Label);
    setSizePolicy(policy);
    adjustSize();
    setMouseTracking(true);
    if(pos>0){
        area=rect();
        area.adjust(arrowTotalLength(),0,arrowTotalLength(),0);
    }
    else area = rect();
}
LinkViewedNodes::LinkButton* LinkViewedNodes::LinkButton::push_next(LinkViewedNodes::LinkButton* next_button){
    if(next_)
        return next_->push_next(next_button);
    else{
        next_ = next_button;
        return next_;
    }
}
int32_t LinkViewedNodes::LinkButton::get_pos() const{
    return pos_;
}
void LinkViewedNodes::LinkButton::set_pos(int32_t pos){
    pos_=pos;
}
void LinkViewedNodes::LinkButton::set_info(INFO_NODE info){
    info_=info;
}
void LinkViewedNodes::LinkButton::erase_next(){
    if(next_){
        LinkViewedNodes* parent = qobject_cast<LinkViewedNodes*>(this->parent());
        assert(parent);
        parent->layout_->removeWidget(next_);
        next_->erase_next();
        delete next_;
        next_=nullptr;
    }
}
LinkViewedNodes::LinkButton* LinkViewedNodes::LinkButton::last(){
    if(next_)
        return next_->last();
    else return this;
}
LinkViewedNodes::LinkButton* LinkViewedNodes::LinkButton::get_next() const{
    return next_;
}
std::vector<INFO_NODE> LinkViewedNodes::LinkButton::get_sequence() const{
    std::vector<INFO_NODE> seq;
    return __get_sequence__(seq);
}
std::vector<INFO_NODE> LinkViewedNodes::LinkButton::__get_sequence__(std::vector<INFO_NODE>& seq) const{
    seq.push_back(info_);
    if(next_){
        return next_->__get_sequence__(seq);
    }
    else return seq;
}

void LinkViewedNodes::LinkButton::draw_link_arrow(QPainter& painter) {
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(palette().text().color());
    painter.setBrush(palette().text().color());

    QLine line({arrowLenght,height()/2},{0,height()/2});

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);
    painter.restore();
}
QSize LinkViewedNodes::LinkButton::sizeHint() const{
    if(pos_>0){
        QSize s = PushLabel::sizeHint();
        s.setWidth(s.width()+arrowTotalLength());
        qDebug()<<"Size: "<<s;
        return s;
    }
    else return PushLabel::sizeHint();
}
void LinkViewedNodes::LinkButton::paintEvent(QPaintEvent* event){
    QRect rect = this->rect();
    QPainter p(this);
    if(pos_>0){
        draw_link_arrow(p);
        rect.adjust(arrowTotalLength(),0,arrowTotalLength(),0);
    }
    else{
        QMargins margins = contentsMargins();
        p.translate(0,-margins.top());
    }
    qDebug()<<"Margin:"<<margin();
    qDebug()<<text();
    qDebug()<<rect;
    p.drawText(rect,0,text());
}
void LinkViewedNodes::LinkButton::mouseMoveEvent(QMouseEvent *event){
    if (area.contains(event->pos())) {
        QFont f(font(),this);
        f.setUnderline(true);
        setFont(f);
        setCursor(Qt::PointingHandCursor);
    } else {
        QFont f(font(),this);
        f.setUnderline(false);
        setFont(f);
        setCursor(Qt::ArrowCursor);
    }
    QWidget::mouseMoveEvent(event);
}
void LinkViewedNodes::LinkButton::mousePressEvent(QMouseEvent *event){
    if(pos_>0){
        if (area.contains(event->pos()))
            emit clicked();
    }
    else emit clicked();
}
void LinkViewedNodes::LinkButton::leaveEvent(QEvent* event){
    QFont f(font(),this);
    f.setUnderline(false);
    setFont(f);
    PushLabel::leaveEvent(event);
}
LinkViewedNodes::LinkViewedNodes(QWidget* parent):QWidget(parent), ObjectFromSettings(this){
    layout_ = new QHBoxLayout(this);
    layout_->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    setContentsMargins(0,0,0,0);
    layout_->setContentsMargins(0,0,0,0);
    setLayout(layout_);
}

void LinkViewedNodes::reset(){
    if(root_){
        root_->erase_next();
        root_->deleteLater();
        root_=nullptr;
    }
    delete layout_;
    layout_ = new QHBoxLayout(this);
    layout_->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    layout_->setContentsMargins(0,0,0,0);
    setLayout(layout_);
    repaint();
}
void LinkViewedNodes::__add_button__(const QString& text, INFO_NODE info){
    LinkViewedNodes::LinkButton* last = nullptr;
    if(root_)
        last = root_->push_next(new LinkViewedNodes::LinkButton(
                             text,this,layout_->count()));
    else {root_= new LinkViewedNodes::LinkButton(
                text,this,layout_->count());
        last = root_;
    }
    layout_->addWidget(last);
    last->set_info(info);
    connect(last,&PushLabel::clicked,this,&LinkViewedNodes::activated_button);
    repaint();
}

void LinkViewedNodes::add_button(INFO_NODE info){
    if(info.is_valid()){
        if(info.has_node()){
            switch(info.parent->type()){
                case(NODE_TYPE::VARIABLE):{
                    __add_button__(QString::fromStdString(
                        dynamic_cast<VariableNode*>(
                        info.parent)->variable()->full_name()
                        ),info);
                    break;
                }
                default:{
                    __add_button__(QString("Id(%1)").arg(info.id),info);
                    break;
                }
            }
        }
        else{

        }
    }
    else{

    }
}

void LinkViewedNodes::activated_button(){
    if(LinkViewedNodes::LinkButton* button = dynamic_cast<LinkViewedNodes::LinkButton*>(QObject::sender())){
        button->erase_next();
        emit update_sequence(root_->get_sequence());
    }
    else assert(true);
}
}
