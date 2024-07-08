#pragma once
#include <QSplitter>
#include <QObject>
#include "dataview/sheets.h"
#include "dataview/expression_view.h"

namespace dataview{

class DataViewSplit:public QSplitter{
    Q_OBJECT
public:
    DataViewSplit(QWidget* parent):QSplitter(Qt::Vertical,parent){
        setObjectName("MainDataView");
        __define_view__();
    }

    Sheets* sheets() const;

private:

    void __define_view__();

    void __define_signals_slots__();

    void __load_settings__();

    void __save_settings__();

    void __load_styles__();

    Sheets* sheets_;
    VarExpressionView* expression_view_;
};
}
