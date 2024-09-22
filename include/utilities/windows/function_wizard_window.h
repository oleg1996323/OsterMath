#pragma once
#include <QWidget>
#include <QMainWindow>
#include "arithmetic_types.h"
#include <QRegularExpression>

namespace utilities{
namespace windows{
class FunctionWizard:public QMainWindow{
    enum FUNCTION_TYPE{
        NONE,
        LN,
        LG10,
        EXP,
        COS,
        ACOS,
        SIN,
        ASIN,
        FACTORIAL,
        LOG_BASE,
        SUM,
        PROD,
        SUMPRODUCT
    };
    Q_OBJECT
public:
    FunctionWizard(QWidget* parent);
    FunctionWizard(QString parsed_text_to_function,QWidget* parent);
private:
    FUNCTION_TYPE parse_entry(const QString&); //TODO add new enum for range and simple functions
    static QRegularExpression function;
    static QRegularExpression var_node;
    static QRegularExpression multiarg_function;
    static QRegularExpression range_function;
};
}
}
