#pragma once
#include <QHBoxLayout>
#include <QTextEdit>
#include <utilities/custom_widgets/buttons.h>

namespace dataview{

class ExpressionButton:public IconedButton{
    Q_OBJECT
public:
    ExpressionButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){

        setContentsMargins(0,0,0,0);
        setFixedSize(45,45);
    }
};

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
