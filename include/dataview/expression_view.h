#pragma once
#include <QHBoxLayout>
#include <QTextEdit>
#include <PushButton.h>
#include <CollapsibleButton.h>

namespace dataview{
class ExpressionTextEdit;
//TODO add signal to open auxiliairy window for formula selection/help
class ExpressionButton:public PushButton{
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
    ExpressionTextEdit* expression_;
    ExpressionButton* formula_expl_;
    CollapseButton* expand_collapse_expl_;

private slots:
    void expand_collapse();
};
}
