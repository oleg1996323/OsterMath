#include "model/nodeview_delegate.h"
#include <QPaintDevice>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QTextItem>
#include <QStyle>
#include "model/nodeview_model.h"

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

void NodeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const{
    painter->save();
    if (option.state & QStyle::State_Selected){
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
        QSize hint = sizeHint(opt, index);

        QRect rect = option.rect;
        painter->setBrush(QColor(255,255,255));
        painter->drawRect(rect);
        style->drawItemText(painter, rect,opt.displayAlignment, opt.palette, true, opt.text, QPalette::Text);
    }
    else if(option.state & QStyle::State_MouseOver){
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
        QSize hint = sizeHint(opt, index);

        QRect rect = option.rect;
        painter->setBrush(QColor(255,255,255));
        painter->setCompositionMode(QPainter::CompositionMode_Darken);
        painter->drawRect(rect);
        style->drawItemText(painter, rect,opt.displayAlignment, opt.palette, true, opt.text, QPalette::Text);
    }
    else{
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
        QSize hint = sizeHint(opt, index);

        QRect rect = option.rect;
        painter->setBrush(option.palette.brush(QPalette::Base));
        painter->drawRect(rect);
        style->drawItemText(painter, rect,opt.displayAlignment, opt.palette, true, opt.text, QPalette::Text);
    }
}

QSize NodeViewDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const{
    return QSize(option.rect.width(), 55);
}
}
