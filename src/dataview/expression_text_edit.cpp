#include "dataview/expression_text_edit.h"
#include <QApplication>
#include <QLineEdit>

namespace dataview{

void ExpressionTextEdit::focusInEvent(QFocusEvent* event){

}
void ExpressionTextEdit::focusOutEvent(QFocusEvent* event){

}
void ExpressionTextEdit::keyPressEvent(QKeyEvent* event){
    switch(event->modifiers()){
    case Qt::Key_Enter:{
        QApplication::instance()->sendEvent(ptr_editor,event);
        ptr_editor = nullptr;
        break;
    }
    case Qt::Key_Escape:{
        //set to ptr_editor old text
        emit focus_to_nodeview_item_edit(ptr_editor);
        ptr_editor = nullptr;
        break;
    }
    default:{
        emit focus_to_nodeview_item_edit(ptr_editor);
        break;
    }
    }
}

void ExpressionTextEdit::enable(bool val){
    setEnabled(val);
}

void ExpressionTextEdit::focus_from_nodeview_item_edit(QLineEdit* item_editor){
    ptr_editor = item_editor;
}
}
