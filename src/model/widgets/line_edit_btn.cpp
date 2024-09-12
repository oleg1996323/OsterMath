#include "model/custom_widgets/line_edit_btn.h"
#include <QModelIndex>
#include <QHBoxLayout>
#include <QPainter>
#include "arithmetic_types.h"
#include "styles/button_style_option.h"
#include "styles/line_edit_style_option.h"
#include <QStylePainter>

namespace model::utilities {
DelegateNodeEditor::DelegateNodeEditor(QWidget* parent,std::unique_ptr<INFO_NODE> info,bool btn_active):
QWidget(parent),
info_(std::move(info))
{
    setContentsMargins(0,0,0,0);
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);
    expr_edit_ = new LineEdit(this);
    expr_edit_->setSizePolicy({QSizePolicy::Expanding,QSizePolicy::Expanding});
    layout_->addWidget(expr_edit_);
    if(btn_active){
        btn_view_node_ = new PushButton("...",this);
        connect(btn_view_node_,&PushButton::clicked,
        this, [this](){
            assert(info_->parent);
            emit show_node(info_->parent,info_->id);
        });
        btn_view_node_->setSizePolicy({QSizePolicy::Expanding,QSizePolicy::Expanding});
        layout_->addWidget(btn_view_node_);
    }
    setLayout(layout_);
}
DelegateNodeEditor::DelegateNodeEditor(QString line_text,QWidget* parent,std::unique_ptr<INFO_NODE> info,bool btn_active):
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
        btn_view_node_ = new PushButton("...",this);
        connect(btn_view_node_,&PushButton::clicked,
        this, [this](){
            assert(info_->parent);
            emit show_node(info_->parent,info_->id);
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
}
