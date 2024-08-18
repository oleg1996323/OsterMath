#include "model/nodeview_delegate.h"
#include <QPaintDevice>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QTextItem>
#include <QLineEdit>
#include "model/nodeview_model.h"
#include "styles/styles.h"

namespace model{

NodeViewDelegate::NodeViewDelegate(QObject* parent):QStyledItemDelegate(parent){

}

QWidget* NodeViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(index.isValid()){
        Node* node = qobject_cast<const model::NodeView*>(index.model())->get_node();
        if(node->type()==NODE_TYPE::VARIABLE){
            if(node->has_child(0)){
                node = node->child(0).get();
                if(index.column()<node->childs().size()){
                    if(index.row()==0)
                        return new QLineEdit(parent);
                    else if(index.row()==1 || node->has_child(index.column()) && node->child(index.column())->has_childs()){
                        return new QLineEdit(parent);
                    }
                    else
                        return nullptr;
                }
                else if(index.column()==node->childs().size()){
                    if(index.row()==0)
                        return new QLineEdit(parent);
                    else if(node->has_child(index.column())){
                        if(node->child(index.column())->has_childs() && index.row()<=node->child(index.column())->childs().size())
                            return new QLineEdit(parent);
                        else return nullptr;
                    }
                    else
                        return nullptr;
                }
                else return nullptr;
            }
            else{
               return nullptr;
            }
        }
        else {
            if(node->has_child(index.column()))
                node = node->child(index.column()).get();
            else return nullptr;
        }
        if(node && node->has_child(index.column())){
            if(node->child(index.column())->is_array())
                return new QPushButton("...",parent);
            else{
                return new QLineEdit(parent);
            }
        }
        else return new QLineEdit(parent);
    }
    return nullptr;
}

void NodeViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if(index.isValid()){
        Node* node = qobject_cast<const model::NodeView*>(index.model())->data(index,Qt::EditRole).value<Node*>();
        assert(node);
        if(node){
            QLineEdit* ptr = qobject_cast<QLineEdit*>(editor);
            std::stringstream stream;
            node->print_text(stream);
            qDebug()<<QString::fromStdString(stream.str());
            ptr->setText(QString::fromStdString(stream.str()));
        }
    }
}

void NodeViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    if(index.isValid() && editor){
        QLineEdit* ptr = qobject_cast<QLineEdit*>(editor);
        model->setData(index,ptr->text(),Qt::DisplayRole);
        //recursive call of printText() if changed in ArrayNode([1,1,1,1])
    }
}

//void NodeViewDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const{
//    QStyledItemDelegate::initStyleOption(option,index);
//    if (option->state & QStyle::State_None){
//        QLinearGradient grad;
//        grad.setSpread(QLinearGradient::ReflectSpread);
//        grad.setStart(option->rect.x(),option->rect.y());
//        grad.setFinalStop(option->rect.width(),option->rect.height());
//        grad.setColorAt(0,option->palette.window().color());
//        grad.setColorAt(0.5,option->palette.button().color());
//        grad.setColorAt(1,option->palette.midlight().color());
//        option->backgroundBrush = grad;
//    }
//    else if (option->state & QStyle::State_Selected){
//        option->features &= QStyleOptionViewItem::WrapText;
//        option->showDecorationSelected = true;
//        option->backgroundBrush.setColor(QColor(255,255,255));
//        option->palette.setBrush(QPalette::Text,QColor(0,0,0));
//    }
//    else if(option->state & QStyle::State_Sibling){
//        return;
//    }
//    else{
//        QLinearGradient grad;
//        grad.setSpread(QLinearGradient::ReflectSpread);
//        grad.setStart(option->rect.x(),option->rect.y());
//        grad.setFinalStop(option->rect.width(),option->rect.height());
//        grad.setColorAt(0,option->palette.window().color());
//        grad.setColorAt(0.5,option->palette.button().color());
//        grad.setColorAt(1,option->palette.midlight().color());
//        option->backgroundBrush = grad;
//    }
//}

//void NodeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const{
////    painter->save();
////    QStyleOptionViewItem opt = option;
////    initStyleOption(&opt,index);
////    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();

////    painter->setBrush(opt.palette.brush(QPalette::Window));
////    painter->drawRect(opt.rect);
////    style->drawItemText(painter, opt.rect,opt.displayAlignment, opt.palette, true, opt.text, QPalette::Text);
////    painter->restore();
//    QStyledItemDelegate::paint(painter,option,index);
//}

QSize NodeViewDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const{
    return QSize(option.rect.width(), 55);
}
}
