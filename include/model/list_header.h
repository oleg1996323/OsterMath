#pragma once
#include <QHeaderView>

namespace model{
class ListHeader:public QHeaderView{
    Q_OBJECT
public:
    ListHeader(QWidget* parent);
};
}
