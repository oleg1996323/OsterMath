#include "model/custom_widgets/line_edit_btn.h"
#include <QModelIndex>
#include <QHBoxLayout>
#include "arithmetic_types.h"

namespace model::utilities {
DelegateNodeEditor::DelegateNodeEditor(QWidget* parent,std::unique_ptr<INFO_NODE> info,bool btn_active):
QWidget(parent),
info_(std::move(info))
{
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    expr_edit_ = new QLineEdit(this);
    layout_->addWidget(expr_edit_);
    if(btn_active){
        btn_view_node_ = new QPushButton(this);
        connect(btn_view_node_,&QPushButton::clicked,
        this, [this](){
            assert(info_->parent);
            emit show_node(info_->parent,info_->id);
        });
        layout_->addWidget(btn_view_node_);
    }
}
DelegateNodeEditor::DelegateNodeEditor(QString line_text,QWidget* parent,std::unique_ptr<INFO_NODE> info,bool btn_active):
QWidget(parent),
info_(std::move(info))
{
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    expr_edit_ = new QLineEdit(line_text,this);
    layout_->addWidget(expr_edit_);
    if(btn_active){
        btn_view_node_ = new QPushButton(this);
        connect(btn_view_node_,&QPushButton::clicked,
        this, [this](){
            assert(info_->parent);
            emit show_node(info_->parent,info_->id);
        });
        layout_->addWidget(btn_view_node_);
    }
}
void DelegateNodeEditor::set_text(QString text){
    expr_edit_->setText(text);
}
void DelegateNodeEditor::enable_btn(bool arg){
    btn_view_node_->setEnabled(arg);
}
void DelegateNodeEditor::enable_editing(bool arg){
    expr_edit_->setEnabled(arg);
}
}
