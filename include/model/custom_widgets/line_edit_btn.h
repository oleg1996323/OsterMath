#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

class Node;
class INFO_NODE;
namespace model::utilities {
namespace __sub_widgets__{
class LineEdit:public QLineEdit{
    Q_OBJECT
    Q_PROPERTY(bool borders_ READ borders WRITE setBorders)
    Q_PROPERTY(int border_radius_ READ border_radius WRITE setBorder_radius)
    Q_PROPERTY(bool rounded_borders_ READ rounded_borders WRITE setRounded_borders)
public:
    LineEdit(QWidget* parent):QLineEdit(parent){}
    LineEdit(QString text,QWidget* parent):QLineEdit(text,parent){}
    bool borders() const;
    void setBorders(bool);
    int border_radius() const;
    void setBorder_radius(int);
    bool rounded_borders() const;
    void setRounded_borders(bool);
protected:
    virtual void paintEvent(QPaintEvent*) override;
private:
    int border_radius_;
    bool borders_;
    bool rounded_borders_;
};

class Button:public QPushButton{
    Q_OBJECT
public:
    Button(QString text,QWidget* parent):QPushButton(text,parent){}
    Button(QWidget* parent):QPushButton(parent){}
protected:
    virtual void paintEvent(QPaintEvent*) override;
};
}
class DelegateNodeEditor:public QWidget{
    Q_OBJECT
public:
    DelegateNodeEditor(QWidget* parent,std::unique_ptr<INFO_NODE>,bool);
    DelegateNodeEditor(QString,QWidget* parent,std::unique_ptr<INFO_NODE>,bool);
    void set_text(QString);
    void enable_btn(bool);
    void enable_editing(bool);
    QString text() const noexcept;

signals:
    void show_node(Node*,size_t);
private:

    //TODO connect with ExpressionTextEdit
    __sub_widgets__::Button* btn_view_node_;
    __sub_widgets__::LineEdit* expr_edit_;
    std::unique_ptr<INFO_NODE> info_;
};
}
