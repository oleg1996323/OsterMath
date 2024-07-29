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
    private:
        virtual void __retranslate__() override;
        static QPalette style_;
    };
}


