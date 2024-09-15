#include "model/nodeview_delegate.h"
#include <QPaintDevice>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QTextItem>
#include <QLineEdit>
#include <bookmath.h>
#include "model/nodeview_model.h"
#include "styles/styles.h"
#include "model/custom_widgets/line_edit_btn.h"

namespace model{

NodeViewDelegate::NodeViewDelegate(QObject* parent):QStyledItemDelegate(parent){
    setObjectName("node_view_delegate");
}

QWidget* NodeViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(index.isValid()){
        std::shared_ptr<Node> node = qobject_cast<const model::NodeView*>(index.model())->get_node().node();
        INFO_NODE info;
        bool btn_need=false;
        utilities::DelegateNodeEditor* editor = nullptr;
        if(node){
            //case when child exists
            if(!node->has_childs()){
                if(index.row()==0 && index.column()==0)
                    btn_need=false;
                else return nullptr;
            }
            else if(node->is_array()){
                if(index.column()<node->childs().size()){
                    if(node->child(index.column())->is_array()){
                        if(index.row()<node->child(index.column())->childs().size()){
                            btn_need = true;
                            info={node->child(index.column()).get(),index.row()};
                        }
                        else if(index.row()==node->child(index.column())->childs().size()){
                            btn_need = false;
                            info={node->child(index.column()).get(),index.row()};
                        }
                        else return nullptr;
                    }
                    else{
                        if(index.row()==0){
                            btn_need = true;
                            info={node->child(index.column()).get(),index.column()};
                        }
                        else if(index.row()==1){
                            btn_need = false;
                        }
                        else return nullptr;
                    }
                }
                else if(index.column()==node->childs().size()){
                    if(index.row()==0 && index.column()==0){
                        btn_need = true;
                        info={node.get(),index.column()};
                    }
                    else if(index.row()==0 && index.column()!=0){
                        btn_need = false;
                        info={node.get(),index.column()};
                    }
                    else return nullptr;
                }
                else return nullptr;
            }
            else{
                if(index.column()==0)
                    if(index.row()<=1){
                        btn_need = false;
                    }
                    else return nullptr;
                else if(index.column()==1){
                    if(index.row()==0){
                        btn_need = false;
                    }
                    else return nullptr;
                }
                else return nullptr;
            }
        }
        else return nullptr;
        editor = new utilities::DelegateNodeEditor(parent,std::make_unique<INFO_NODE>(info),btn_need);
        if(btn_need)
            connect(editor,&utilities::DelegateNodeEditor::show_node,
            this, [this](Node* parent,size_t id){
                emit show_node(parent,id);
            });
        return editor;
    }
    else return nullptr;
}

void NodeViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if(index.isValid()){
        if(Node* node = qobject_cast<const model::NodeView*>(index.model())->data(index,Qt::EditRole).value<Node*>()){
            if(utilities::DelegateNodeEditor* ptr = qobject_cast<utilities::DelegateNodeEditor*>(editor)){
                std::stringstream stream;
                node->print_text(stream);
                qDebug()<<QString::fromStdString(stream.str());
                ptr->set_text(QString::fromStdString(stream.str()));
            }
        }
    }
}

void NodeViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    if(index.isValid() && editor){
        if(utilities::DelegateNodeEditor* ptr = qobject_cast<utilities::DelegateNodeEditor*>(editor)){
            qDebug()<<ptr->text();
            model->setData(index,ptr->text(),Qt::DisplayRole);
        }
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
