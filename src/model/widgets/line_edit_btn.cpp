#include "model/custom_widgets/line_edit_btn.h"
#include <QModelIndex>
#include <QHBoxLayout>
#include <QPainter>
#include "arithmetic_types.h"
#include "styles/button_style_option.h"
#include "styles/line_edit_style_option.h"
#include "kernel/application.h"
#include <QStylePainter>

namespace model::utilities {
DelegateNodeEditor::DelegateNodeEditor(QWidget* parent,std::vector<INFO_NODE>&& info,bool btn_active):
QWidget(parent),
info_(std::move(info))
{
    setContentsMargins(0,0,0,0);
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);
    expr_edit_ = new LineEdit(this);
    expr_edit_->setMinimumSize({0,0});
    expr_edit_->setSizePolicy({QSizePolicy::Expanding,QSizePolicy::Expanding});
    layout_->addWidget(expr_edit_);
    if(btn_active){
        if(kernel::settings::Program::get_theme()==Themes::Dark)
            btn_view_node_ = new IconedButton(":/nodeview/node_view/show_node_dark.png",this);
        else
            btn_view_node_ = new IconedButton(":/nodeview/node_view/show_node_light.png",this);
        btn_view_node_->setBorders(false);
        btn_view_node_->set_size({DelegateNodeEditor::height(),DelegateNodeEditor::height()});
        connect(btn_view_node_,&PushButton::clicked,
        this, [this](){
            assert(!info_.empty());
            emit show_node(info_);
        });
        layout_->addWidget(btn_view_node_);
    }
    setLayout(layout_);
}
DelegateNodeEditor::DelegateNodeEditor(QString line_text,QWidget* parent,std::vector<INFO_NODE>&& info,bool btn_active):
QWidget(parent),
info_(std::move(info))
{
    setContentsMargins(0,0,0,0);
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);
    expr_edit_ = new LineEdit(line_text,this);
    expr_edit_->setSizePolicy({QSizePolicy::Expanding,QSizePolicy::Expanding});
    layout_->addWidget(expr_edit_);
    if(btn_active){
        if(kernel::settings::Program::get_theme()==Themes::Dark)
            btn_view_node_ = new IconedButton("nodeview/node_view/show_node_dark.png",this);
        else
            btn_view_node_ = new IconedButton("nodeview/node_view/show_node_light.png",this);
        btn_view_node_->setBorders(false);
        btn_view_node_->set_size({DelegateNodeEditor::height(),DelegateNodeEditor::height()});
        connect(btn_view_node_,&PushButton::clicked,
        this, [this](){
            assert(!info_.empty());
            emit show_node(info_);
        });
        btn_view_node_->setSizePolicy({QSizePolicy::Expanding,QSizePolicy::Expanding});
        layout_->addWidget(btn_view_node_);
    }
    setLayout(layout_);
}
void DelegateNodeEditor::set_text(QString text){
    expr_edit_->setText(text);
}
void DelegateNodeEditor::enable_btn(bool arg){
    if(btn_view_node_)
        btn_view_node_->setEnabled(arg);
}
void DelegateNodeEditor::enable_editing(bool arg){
    expr_edit_->setEnabled(arg);
}
QString DelegateNodeEditor::text() const noexcept{
    return expr_edit_->text();
}
LineEdit* DelegateNodeEditor::editor() const{
    return expr_edit_;
}
bool DelegateNodeEditor::event(QEvent* event){
    if(event->type()==QEvent::KeyPress){
        return expr_edit_->event(event);
    }
    else return QWidget::event(event);
}

const std::vector<INFO_NODE>& DelegateNodeEditor::info() const{
    return info_;
}
}
