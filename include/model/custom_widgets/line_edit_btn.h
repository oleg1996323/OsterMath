#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include "PushButton.h"
#include "LineEdit.h"

class Node;
class INFO_NODE;
namespace model::utilities {
class DelegateNodeEditor:public QWidget{
    Q_OBJECT
public:
    DelegateNodeEditor(QWidget* parent,std::vector<INFO_NODE>&&,bool);
    DelegateNodeEditor(QString,QWidget* parent,std::vector<INFO_NODE>&&,bool);
    void set_text(QString);
    void enable_btn(bool);
    void enable_editing(bool);
    QString text() const noexcept;
    LineEdit* editor() const;
    const std::vector<INFO_NODE>& info() const;
signals:
    void show_node(const std::vector<INFO_NODE>&);
protected:
    virtual bool event(QEvent*) override;
private:

    //TODO connect with ExpressionTextEdit
    IconedButton* btn_view_node_;
    LineEdit* expr_edit_;
    std::vector<INFO_NODE> info_;
};
}
