#include "model/nodeview_delegate.h"
#include <QPaintDevice>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QTextItem>
#include <QStyle>
#include "model/nodeview_model.h"
#include "styles/styles.h"

namespace model{

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
    //QStyledItemDelegate::initStyleOption(option,index);
    if (option->state & QStyle::State_None){
        QLinearGradient grad;
        grad.setStart(option->rect.x(),option->rect.y());
        grad.setFinalStop(option->rect.width(),option->rect.height());
        grad.setColorAt(0,option->palette.window().color());
        grad.setColorAt(0.5,option->palette.button().color());
        grad.setColorAt(1,option->palette.midlight().color());
        option->backgroundBrush = grad;
    }
    else if (option->state & QStyle::State_Selected){
        option->palette.setBrush(QPalette::Window,QColor(255,255,255));
        option->palette.setBrush(QPalette::Text,QColor(0,0,0));
    }
    else{
        QLinearGradient grad;
        grad.setSpread(QLinearGradient::ReflectSpread);
        grad.setStart(option->rect.x(),option->rect.y());
        grad.setFinalStop(option->rect.width(),option->rect.height());
        grad.setColorAt(0,option->palette.window().color());
        grad.setColorAt(0.5,option->palette.button().color());
        grad.setColorAt(1,option->palette.midlight().color());
        option->backgroundBrush = grad;
    }
}

void NodeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const{
//    painter->save();
//    QStyleOptionViewItem opt = option;
//    initStyleOption(&opt,index);
//    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();

//    painter->setBrush(opt.palette.brush(QPalette::Window));
//    painter->drawRect(opt.rect);
//    style->drawItemText(painter, opt.rect,opt.displayAlignment, opt.palette, true, opt.text, QPalette::Text);
//    painter->restore();
    QStyledItemDelegate::paint(painter,option,index);
}

QSize NodeViewDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const{
    return QSize(option.rect.width(), 55);
}
}
