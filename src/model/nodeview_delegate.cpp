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
        INFO_NODE info = qobject_cast<const model::NodeView*>(index.model())->get_node();
        std::vector<INFO_NODE> sequence_info;
        std::shared_ptr<Node> node;
        if(info.id>-1 && info.parent->has_child(info.id))
            node = qobject_cast<const model::NodeView*>(index.model())->get_node().node();
        bool btn_need=false;
        utilities::DelegateNodeEditor* editor = nullptr;
        if(node){
            //case when child exists
            if(!node->has_childs()){
                if(index.row()==0 && index.column()==0){
                    btn_need=false;
                    sequence_info.push_back({node.get(),0});
                }
                else return nullptr;
            }
            else if(node->is_array()){
                if(index.column()<node->childs().size()){
                    if(node->child(index.column())->is_array()){
                        if(index.row()<node->child(index.column())->childs().size() &&
                                (node->child(index.column())->child(index.row())->type()==NODE_TYPE::ARRAY ||
                                 node->child(index.column())->child(index.row())->type()==NODE_TYPE::VALUE ||
                                 node->child(index.column())->child(index.row())->type()==NODE_TYPE::VARIABLE)){
                            btn_need = true;
                            sequence_info.push_back({node.get(),index.column()});
                            sequence_info.push_back({node->child(index.column()).get(),index.row()});
                            if(node->child(index.column())->child(index.row())->type()==NODE_TYPE::VALUE ||
                                    node->child(index.column())->child(index.row())->type()==NODE_TYPE::VARIABLE)
                                sequence_info.push_back({node->child(index.column())->child(index.row()).get(),0});
                        }
                        else if(index.row()==node->child(index.column())->childs().size()){
                            btn_need = false;
                            sequence_info.push_back({node.get(),index.column()});
                            sequence_info.push_back({node->child(index.column()).get(),index.row()});
                        }
                        else return nullptr;
                    }
                    else{
                        if(index.row()==0 || index.row()==1){
                            if(node->child(index.column())->type_val() & (TYPE_VAL::VALUE|TYPE_VAL::STRING) ||
                                    node->child(index.column())->type_val()==TYPE_VAL::UNKNOWN){
                                btn_need = false;
                                sequence_info.push_back({node.get(),index.column()});
                            }
                            else{
                                return nullptr; //for FUNCTIONS add another button
                            }
                        }
                        else return nullptr;
                    }
                }
                else if(index.column()==node->childs().size()){
                    if(index.row()==0){
                        btn_need = false;
                        sequence_info.push_back({node.get(),index.column()});
                    }
                    else return nullptr;
                }
                else return nullptr;
            }
            else{
                if(index.column()==0)
                    if(index.row()<=1){
                        btn_need = false;
                        sequence_info.push_back({node.get(),index.column()});
                    }
                    else return nullptr;
                else if(index.column()==1){
                    if(index.row()==0){
                        btn_need = false;
                        sequence_info.push_back({node.get(),index.column()});
                    }
                    else return nullptr;
                }
                else return nullptr;
            }
        }
        else{
            btn_need = false;
        }
        editor = new utilities::DelegateNodeEditor(parent,std::move(sequence_info),btn_need);
        if(btn_need)
            connect(editor,&utilities::DelegateNodeEditor::show_node,[this,editor, index](const std::vector<INFO_NODE>&){
                if(const NodeView* this_view = qobject_cast<const NodeView*>(index.model())){
                    const_cast<NodeView*>(this_view)->set_representable_child_node(editor->info());
                }
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
                stream<<'=';
                node->print_text(stream);
                qDebug()<<QString::fromStdString(stream.str());
                ptr->set_text(QString::fromStdString(stream.str()));
            }
        }
}}
void NodeViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    if(index.isValid() && editor){
        if(utilities::DelegateNodeEditor* ptr = qobject_cast<utilities::DelegateNodeEditor*>(editor)){
            if(Node* node = qobject_cast<const model::NodeView*>(index.model())->data(index,Qt::EditRole).value<Node*>()){
                qDebug()<<ptr->text();
                std::stringstream stream;
                stream<<'=';
                node->print_text(stream);
                if(ptr->text()!=QString::fromStdString(stream.str()))
                    model->setData(index,ptr->text(),Qt::DisplayRole);
                else return;
            }
            else{
                if(!ptr->text().isEmpty()){
                    qDebug()<<ptr->text();
                    model->setData(index,ptr->text(),Qt::DisplayRole);
                }
            }
        }}}

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
