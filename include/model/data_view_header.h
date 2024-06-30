#pragma once
#include <QHeaderView>

class VariableBase;

namespace model {
    class DataViewHeader:public QHeaderView{

    public:
        virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

    private:
        std::unique_ptr<VariableBase> var_;
    };
}


