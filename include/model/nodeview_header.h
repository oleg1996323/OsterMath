#pragma once
#include <QHeaderView>
#include "kernel/def.h"
#include "model/def.h"
#include "model/utilities/hierarchicalheaderview.h"

class VariableBase;

namespace model {
    class NodeViewHeader:public HierarchicalHeaderView, public Retranslatable{
        Q_OBJECT
    public:
        NodeViewHeader(QWidget* parent);
    private:
        virtual void __retranslate__() override;
    };
}


