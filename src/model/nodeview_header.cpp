#include "model/nodeview_header.h"
#include "model/varlist_model.h"
#include "types.h"
#include "arithmetic_functions.h"
#include <QStyle>
#include <QAbstractItemModel>
#include <memory>

namespace model {

NodeViewHeader::NodeViewHeader(QWidget* parent):QHeaderView(Qt::Horizontal,parent){

}

//void NodeViewHeader::recurse_paintSection(QPainter *painter, const QRect &rect, int logicalIndex, ChildsMeasure* str_section) const{
//    const size_t depth = str_section->max_size_depth;
//    for (int i = 0; i < depth; ++i) {
//        QSize cellSize = {400,20};
//        QRect sectionRect(rect);

//        sectionRect.setTop(str_section->max_size_depth*20); // distance from 0 to i-1 rows

//        sectionRect.setSize(cellSize);

//        // draw section with style
//        QStyleOptionHeader opt;
//        initStyleOption(&opt);
//        opt.textAlignment = Qt::AlignCenter;
//        opt.iconAlignment = Qt::AlignVCenter;
//        opt.section = logicalIndex;
//        opt.text = 1; //indexes of arrays
//        opt.rect = sectionRect;

//        //QVariant bg = cellIndex.data(Qt::BackgroundRole);
//        //QVariant fg = cellIndex.data(Qt::ForegroundRole);
////        if (bg.canConvert<QBrush>()) {
////            opt.palette.setBrush(QPalette::Button, bg.value<QBrush>());
////            opt.palette.setBrush(QPalette::Window, bg.value<QBrush>());
////        }
////        if (fg.canConvert<QBrush>()) {
////            opt.palette.setBrush(QPalette::ButtonText, fg.value<QBrush>());
////        }

//        painter->save();
//        style()->drawControl(QStyle::CE_Header, &opt, painter, this);
//        painter->restore();
//    }
//}

//void NodeViewHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const{
//    if(rootIndex().isValid()){
//        const Variables *model =
//                qobject_cast<Variables *>(this->model());
//        assert(model);
//        ChildsMeasure section_sizes;
//        QModelIndex var = model->index(0,logicalIndex, rootIndex());
//        if(var.isValid()){
//            Result init = var.data(Qt::EditRole).value<Result>();
//            if(init.is_node() && init.get<Node*>()->is_array() && init.get<Node*>()->has_childs()){
//                define_section_subelements(section_sizes,reinterpret_cast<ArrayNode*>(init.get<Node*>()));
//                recurse_paintSection(painter,rect,logicalIndex,&section_sizes);
//            }
//        }
//    }
//}


void NodeViewHeader::__retranslate__(){

}

}
