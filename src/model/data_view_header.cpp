#include "model/data_view_header.h"
#include "model/varlistmodel.h"
#include "types.h"
#include "arithmetic_functions.h"
#include <QStyle>
#include <memory>

namespace model {


void define_section_subelements(STRUCT_SECTION& section_sizes, ArrayNode* array){
    if(array->has_childs()){
        section_sizes.size_=array->childs().size();
        for(std::shared_ptr<Node> child:*array){
            if(child->is_array()){
                section_sizes.childs_.push_back(STRUCT_SECTION(&section_sizes));
                define_section_subelements(section_sizes.childs_.back(), reinterpret_cast<ArrayNode*>(child->execute().get<Node*>()));
                section_sizes.childs_.back().update_max_size_depth();
            }
        }
    }
}

void DataViewHeader::recurse_paintSection(QPainter *painter, const QRect &rect, int logicalIndex, STRUCT_SECTION* str_section){
    const size_t depth = str_section->max_size_depth;
    for (int i = 0; i < depth; ++i) {
        QSize cellSize = {400,20};
        QRect sectionRect(rect);

        sectionRect.setTop(str_section->max_size_depth*20); // distance from 0 to i-1 rows

        sectionRect.setSize(cellSize);

        // draw section with style
        QStyleOptionHeader opt;
        initStyleOption(&opt);
        opt.textAlignment = Qt::AlignCenter;
        opt.iconAlignment = Qt::AlignVCenter;
        opt.section = logicalIndex;
        opt.text = 1; //indexes of arrays
        opt.rect = sectionRect;

        //QVariant bg = cellIndex.data(Qt::BackgroundRole);
        //QVariant fg = cellIndex.data(Qt::ForegroundRole);
//        if (bg.canConvert<QBrush>()) {
//            opt.palette.setBrush(QPalette::Button, bg.value<QBrush>());
//            opt.palette.setBrush(QPalette::Window, bg.value<QBrush>());
//        }
//        if (fg.canConvert<QBrush>()) {
//            opt.palette.setBrush(QPalette::ButtonText, fg.value<QBrush>());
//        }

        painter->save();
        style()->drawControl(QStyle::CE_Header, &opt, painter, this);
        painter->restore();
    }
}

void DataViewHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const{
    const Variables *model =
            qobject_cast<Variables *>(this->model());

    STRUCT_SECTION section_sizes;
    if(var_->is_array() && var_->node()->has_childs())
        define_section_subelements(section_sizes,reinterpret_cast<ArrayNode*>(var_->node().get()));


    const size_t depth = section_sizes.max_size_depth;
    for (int i = 0; i < depth; ++i) {

    }
}

}
