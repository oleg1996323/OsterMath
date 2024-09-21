#include "dataview/link_viewed_nodes.h"
#include "arithmetic_types.h"
#include <QHBoxLayout>

namespace dataview{

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

utilities::LinkButton::LinkButton(QString text,QWidget* parent):PushLabel(text,parent){}

int utilities::LinkButton::get_pos() const{
    return pos_;
}
void utilities::LinkButton::set_pos(int pos){
    pos_=pos;
}

LinkViewedNodes::LinkViewedNodes(QWidget* parent):QWidget(parent), ObjectFromSettings(this){
    layout_ = new QHBoxLayout(this);
    layout_->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    setFixedHeight(30);
    setLayout(layout_);
}

void LinkViewedNodes::reset(){
    sequence_button_.clear();
    sequence_info_.clear();
    for(int i=0;i<layout_->count();++i)
        layout_->removeWidget();
    layout_ = new QHBoxLayout(this);
    setLayout(layout_);
    repaint();
}

void LinkViewedNodes::__add_button__(const QString& text, INFO_NODE info){
    layout_->addWidget(sequence_button_.emplace_back(new utilities::LinkButton(
                    "<A HREF=\"\">"+text+"</A>",this)));
    sequence_info_.push_back(info);
    assert(sequence_button_.size()>0);
    assert(sequence_button_.size()==sequence_info_.size());
    sequence_button_.back()->set_pos(sequence_button_.size()-1);
    connect(sequence_button_.back(),&utilities::LinkButton::linkActivated,this,&LinkViewedNodes::activated_button);
    repaint();
}

void LinkViewedNodes::add_button(INFO_NODE info){
    if(info.is_valid()){
        if(info.has_node()){
            switch(info.parent->type()){
                case(NODE_TYPE::VARIABLE):{
                    __add_button__(QString::fromStdString(
                        reinterpret_cast<VariableNode*>(
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

void LinkViewedNodes::activated_button(const QString& text){
    if(PushLabel* button = qobject_cast<PushLabel*>(QObject::sender())){
        utilities::LinkButton* link_btn = reinterpret_cast<utilities::LinkButton*>(button);
        assert(link_btn->get_pos()<sequence_button_.size());
        assert(sequence_button_.size()==sequence_info_.size());
        assert(link_btn->get_pos()>-1);
        sequence_info_.resize(link_btn->get_pos()+1);
        sequence_button_.resize(link_btn->get_pos()+1);
        emit update_sequence(sequence_info_);
    }
    else assert(true);
}
}
