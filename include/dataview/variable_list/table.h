#pragma once
#include <QTableView>
#include "kernel/def.h"
#include "arithmetic_types.h"

namespace model{
class Variables;
}

namespace dataview{

class Table:public QTableView, public Retranslatable{
    model::Variables* var_list_;
public:
    Table(QWidget* parent);

    virtual void retranslate() override{
        //            QTableWidgetItem *___qtablewidgetitem = horizontalHeaderItem(0);
        //            ___qtablewidgetitem->setText(QCoreApplication::translate("BookMath", "\320\230\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
        //            QTableWidgetItem *___qtablewidgetitem1 = horizontalHeaderItem(1);
        //            ___qtablewidgetitem1->setText(QCoreApplication::translate("BookMath", "\320\242\320\270\320\277", nullptr));
        //            QTableWidgetItem *___qtablewidgetitem2 = horizontalHeaderItem(2);
        //            ___qtablewidgetitem2->setText(QCoreApplication::translate("BookMath", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
    }

signals:
    void open_node(Node*);

public slots:
    void changed_data_base(const QString& name);
    void deleted_data_base(const QString& name);
};
}
