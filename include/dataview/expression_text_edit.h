#pragma once
#include <QTextEdit>
#include <QFocusEvent>

class QLineEdit;
namespace dataview{
class ExpressionTextEdit:public QTextEdit{
    Q_OBJECT
    QLineEdit* ptr_editor;
public:
    ExpressionTextEdit(QWidget* parent):QTextEdit(parent){
        setObjectName("expressionEditor");
        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
        setMinimumHeight(QFontMetrics(font()).height()+contentsMargins().top()+contentsMargins().bottom());
        setGeometry(pos().x(),pos().y(),width(),QFontMetrics(font()).height()+contentsMargins().top()+contentsMargins().bottom());
    }
signals:
    void focus_to_nodeview_item_edit(QLineEdit*);
protected:
    virtual void focusInEvent(QFocusEvent*) override;
    virtual void focusOutEvent(QFocusEvent*) override;
    virtual void keyPressEvent(QKeyEvent*) override;
public slots:
    void focus_from_nodeview_item_edit(QLineEdit*);
    void enable(bool);
    void editor_destroyed();
};
}
