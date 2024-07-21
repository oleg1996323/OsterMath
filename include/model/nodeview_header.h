#pragma once
#include <QHeaderView>
#include "kernel/def.h"
#include "model/def.h"

class VariableBase;

namespace model {
    class NodeViewHeader:public QHeaderView, public Retranslatable{
        Q_OBJECT
    public:
        NodeViewHeader(QWidget* parent);
        virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
        virtual void setModel(QAbstractItemModel*) override;
    private:
        void recurse_paintSection(QPainter *painter, const QRect &rect, int logicalIndex, ChildsMeasure* str_section) const;
        virtual void __retranslate__() override;
    };
}


