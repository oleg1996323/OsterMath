#pragma once
#include <QHeaderView>
#include "model/def.h"

class VariableBase;

namespace model {
    class DataViewHeader:public QHeaderView{
        Q_OBJECT
    public:
        virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

    private:
        std::unique_ptr<VariableBase> var_;

        void recurse_paintSection(QPainter *painter, const QRect &rect, int logicalIndex, ChildsMeasure* str_section) const;
    };
}


