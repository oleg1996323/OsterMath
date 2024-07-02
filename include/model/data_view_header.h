#pragma once
#include <QHeaderView>

class VariableBase;

namespace model {
    struct STRUCT_SECTION{
        STRUCT_SECTION(STRUCT_SECTION* parent = nullptr):parent_(parent){}

        void update_max_size_depth(){
            if(parent_ && parent_->max_size_depth<=max_size_depth)
                parent_->max_size_depth=max_size_depth+1;
        }

        std::vector<STRUCT_SECTION> childs_;
        STRUCT_SECTION* parent_;
        size_t size_=0;
        size_t max_size_depth = 0;
    };

    class DataViewHeader:public QHeaderView{
        Q_OBJECT
    public:
        virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

    private:
        std::unique_ptr<VariableBase> var_;

        void recurse_paintSection(QPainter *painter, const QRect &rect, int logicalIndex, STRUCT_SECTION* str_section);
    };
}


