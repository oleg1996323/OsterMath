#pragma once
#include <QHBoxLayout>
#include <QTextEdit>
#include <PushButton.h>
#include <CollapsibleButton.h>
#include <kernel/def.h>

namespace dataview{
class ExpressionTextEdit;
//TODO add signal to open auxiliairy window for formula selection/help
class ExpressionButton:public IconedButton, public ObjectFromSettings{
    Q_OBJECT
public:
    ExpressionButton(const QString& res_path,QWidget* parent);
public:
    void open_at_clicked();
private:
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
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
