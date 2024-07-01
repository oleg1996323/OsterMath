#include "model/data_view_header.h"
#include "model/varlistmodel.h"
#include "types.h"
#include "arithmetic_functions.h"
#include <QStyle>
#include <memory>

namespace model {

struct STRUCT_SECTION{
    STRUCT_SECTION(STRUCT_SECTION* parent = nullptr):parent(parent){}

    void update_max_size_depth(){
        if(parent_ && parent_->max_size_depth<=max_size_depth)
            parent_->max_size_depth=max_size_depth+1;
    }

    std::vector<STRUCT_SECTION> childs_;
    STRUCT_SECTION* parent_;
    size_t size_=0;
    size_t max_size_depth = 0;
};

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

void DataViewHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const{
    const Variables *model =
            qobject_cast<Variables *>(this->model());

    STRUCT_SECTION section_sizes;
    if(var_->is_array() && var_->node()->has_childs())
        define_section_subelements(section_sizes,reinterpret_cast<ArrayNode*>(var_->node().get()));



    const size_t depth = sz_depth_measure.size();
    for (int i = 0; i < depth; ++i) {
        QModelIndex cellIndex = model->index(i, logicalIndex);
        QSize cellSize = {400,20};
        QRect sectionRect(rect);

        sectionRect.setTop(rowSpanSize(logicalIndex, 0, i)); // distance from 0 to i-1 rows

        sectionRect.setSize(cellSize);

        // draw section with style
        QStyleOptionHeader opt;
        initStyleOption(&opt);
        opt.textAlignment = Qt::AlignCenter;
        opt.iconAlignment = Qt::AlignVCenter;
        opt.section = logicalIndex;
        opt.text = cellIndex.data(Qt::DisplayRole).toString();
        opt.rect = sectionRect;

        QVariant bg = cellIndex.data(Qt::BackgroundRole);
        QVariant fg = cellIndex.data(Qt::ForegroundRole);
        if (bg.canConvert<QBrush>()) {
            opt.palette.setBrush(QPalette::Button, bg.value<QBrush>());
            opt.palette.setBrush(QPalette::Window, bg.value<QBrush>());
        }
        if (fg.canConvert<QBrush>()) {
            opt.palette.setBrush(QPalette::ButtonText, fg.value<QBrush>());
        }

        painter->save();
        style()->drawControl(QStyle::CE_Header, &opt, painter, this);
        painter->restore();
    }
}

}
