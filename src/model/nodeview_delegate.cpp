#include "model/nodeview_delegate.h"
#include <QPaintDevice>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QTextItem>
#include <QStyle>
#include "model/nodeview_model.h"
#include "kernel/styles.h"

namespace model{

QPalette NodeViewDelegate::default_style_ = []{
    QPalette res;
    res.setColor(QPalette::Window,QColor(230,230,230));
    res.setColor(QPalette::WindowText,QColor(0,0,0));
    res.setColor(QPalette::Base,QColor(0,0,0));
    res.setColor(QPalette::AlternateBase,QColor(0,0,0));
    res.setColor(QPalette::ToolTipBase,QColor(0,0,0));
    res.setColor(QPalette::ToolTipText,QColor(0,0,0));
    res.setColor(QPalette::PlaceholderText,QColor(0,0,0));
    res.setColor(QPalette::Text,QColor(0,0,0));
    res.setColor(QPalette::Button,Themes::Palette::get().color(QPalette::Button));
    res.setColor(QPalette::ButtonText,QColor(0,0,0));
    res.setColor(QPalette::BrightText,QColor(0,0,0));

    QColor button = res.color(QPalette::Button);
    res.setColor(QPalette::Light,QColor(230,230,230));
    res.setColor(QPalette::Midlight,QColor(200,200,200));
    res.setColor(QPalette::Dark,QColor(button.red()-20,button.green()-20,button.blue()-20));
    res.setColor(QPalette::Mid,QColor(50,50,50));
    res.setColor(QPalette::Shadow,QColor(20,20,20));
    return res;
}();

QPalette NodeViewDelegate::select_style_= []{
    QPalette res;
    res.setColor(QPalette::Window,QColor(230,230,230));
    res.setColor(QPalette::WindowText,QColor(0,0,0));
    res.setColor(QPalette::Base,QColor(0,0,0));
    res.setColor(QPalette::AlternateBase,QColor(0,0,0));
    res.setColor(QPalette::ToolTipBase,QColor(0,0,0));
    res.setColor(QPalette::ToolTipText,QColor(0,0,0));
    res.setColor(QPalette::PlaceholderText,QColor(0,0,0));
    res.setColor(QPalette::Text,QColor(0,0,0));
    res.setColor(QPalette::Button,Themes::Palette::get().color(QPalette::Button));
    res.setColor(QPalette::ButtonText,QColor(0,0,0));
    res.setColor(QPalette::BrightText,QColor(0,0,0));

    QColor button = res.color(QPalette::Button);
    res.setColor(QPalette::Light,QColor(230,230,230));
    res.setColor(QPalette::Midlight,QColor(200,200,200));
    res.setColor(QPalette::Dark,QColor(button.red()-20,button.green()-20,button.blue()-20));
    res.setColor(QPalette::Mid,QColor(50,50,50));
    res.setColor(QPalette::Shadow,QColor(20,20,20));
    return res;
}();
QPalette NodeViewDelegate::mouse_on_style_= []{
    QPalette res;
    res.setColor(QPalette::Window,QColor(230,230,230));
    res.setColor(QPalette::WindowText,QColor(0,0,0));
    res.setColor(QPalette::Base,QColor(0,0,0));
    res.setColor(QPalette::AlternateBase,QColor(0,0,0));
    res.setColor(QPalette::ToolTipBase,QColor(0,0,0));
    res.setColor(QPalette::ToolTipText,QColor(0,0,0));
    res.setColor(QPalette::PlaceholderText,QColor(0,0,0));
    res.setColor(QPalette::Text,QColor(0,0,0));
    res.setColor(QPalette::Button,Themes::Palette::get().color(QPalette::Button));
    res.setColor(QPalette::ButtonText,QColor(0,0,0));
    res.setColor(QPalette::BrightText,QColor(0,0,0));

    QColor button = res.color(QPalette::Button);
    res.setColor(QPalette::Light,QColor(230,230,230));
    res.setColor(QPalette::Midlight,QColor(200,200,200));
    res.setColor(QPalette::Dark,QColor(button.red()-20,button.green()-20,button.blue()-20));
    res.setColor(QPalette::Mid,QColor(50,50,50));
    res.setColor(QPalette::Shadow,QColor(20,20,20));
    return res;
}();

NodeViewDelegate::NodeViewDelegate(QObject* parent):QStyledItemDelegate(parent){}

QWidget* NodeViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(index.isValid()){
        Node* node = qobject_cast<const model::NodeView*>(index.model())->get_node();
        if(node && node->has_child(index.column())){
            if(node->child(index.column())->is_array())
                return new QPushButton("...",parent);
            else{
                return new QLineEdit(parent);
            }
        }
    }
    return nullptr;
}

void NodeViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if(index.isValid()){
        Node* node = qobject_cast<const model::NodeView*>(index.model())->get_node();
        if(node && node->has_child(index.column())){
            if(!node->child(index.column())->is_array()){
                auto ptr = qobject_cast<QLineEdit*>(editor);
                std::stringstream stream;
                node->child(index.column())->print_result(stream);
                ptr->setText(QString::fromStdString(stream.str()));
                ;
            }
            }
        }
    }

void NodeViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{

}

void NodeViewDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const{
    QStyledItemDelegate::initStyleOption(option,index);
    if (option->state & QStyle::State_Selected){
        QStyle *style = option->widget ? option->widget->style() : QApplication::style();
        QSize hint = sizeHint(*option, index);

        QRect rect = option->rect;
        option->palette.setBrush(QPalette::Window,QColor(255,255,255));
        option->palette.setBrush(QPalette::Text,QColor(255,0,0));
    }
    else if (option->state & QStyle::State_Selected){
        QStyle *style = option->widget ? option->widget->style() : QApplication::style();
        QSize hint = sizeHint(*option, index);

        QRect rect = option->rect;
        option->palette.setBrush(QPalette::Window,QColor(255,255,255));
        option->palette.setBrush(QPalette::Text,QColor(255,255,255));
    }
    else{
        QStyle *style = option->widget ? option->widget->style() : QApplication::style();
        QSize hint = sizeHint(*option, index);

        QRect rect = option->rect;
        option->palette.setBrush(QPalette::Window,QColor(255,255,255));
        option->palette.setBrush(QPalette::Text,QColor(0,0,0));
        option->backgroundBrush = QLinearGradient(0,0,rect.width(),rect.height());
    }
}

void NodeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const{
    painter->save();
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt,index);
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();

    painter->setBrush(opt.palette.brush(QPalette::Window));
    painter->drawRect(opt.rect);
    style->drawItemText(painter, opt.rect,opt.displayAlignment, opt.palette, true, opt.text, QPalette::Text);
    painter->restore();
}

QSize NodeViewDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const{
    return QSize(option.rect.width(), 55);
}
}
