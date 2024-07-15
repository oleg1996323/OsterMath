#pragma once
#include <QHeaderView>
#include "kernel/def.h"

namespace model{
class VariablesHeader:public QHeaderView, public Retranslatable{
    Q_OBJECT
public:
    VariablesHeader(QWidget* parent);

private:
    virtual void __retranslate__() override;
};
}
