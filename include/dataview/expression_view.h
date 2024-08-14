#pragma once
#include <QHBoxLayout>
#include <QTextEdit>
#include <utilities/custom_widgets/buttons.h>

namespace dataview{

//TODO add signal to open auxiliairy window for formula selection/help
class ExpressionButton:public QPushButton{
    Q_OBJECT
public:
    ExpressionButton(const QString& res_path,QWidget* parent);
};


//TODO add signal to send text for parsing
//add formula autocomplete
//add formula highlight
class VarExpressionView:public QWidget{
    Q_OBJECT
public:
    VarExpressionView(QWidget* parent);
private:
    QHBoxLayout* layout_;
    QTextEdit* expression_;


    ExpressionButton* formula_expl_;
    QPushButton* expand_collapse_expl_;

private slots:
    void expand_collapse();
};
}
