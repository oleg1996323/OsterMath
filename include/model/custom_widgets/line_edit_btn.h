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
    DelegateNodeEditor(QWidget* parent,std::unique_ptr<INFO_NODE>,bool);
    DelegateNodeEditor(QString,QWidget* parent,std::unique_ptr<INFO_NODE>,bool);
    void set_text(QString);
    void enable_btn(bool);
    void enable_editing(bool);
    QString text() const noexcept;
    LineEdit* editor() const;

signals:
    void show_node(Node*,size_t);
protected:
    virtual bool event(QEvent*) override;
private:

    //TODO connect with ExpressionTextEdit
    IconedButton* btn_view_node_;
    LineEdit* expr_edit_;
    std::unique_ptr<INFO_NODE> info_;
};
}
