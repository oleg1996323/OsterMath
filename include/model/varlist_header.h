#pragma once
#include <QHeaderView>
#include "kernel/def.h"

namespace model{
class VariablesHeader:public QHeaderView, public Retranslatable{
    Q_OBJECT
public:
    VariablesHeader(QWidget* parent);
    virtual void retranslate() override;
private:

};
}
