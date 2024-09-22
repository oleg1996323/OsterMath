#include "utilities/windows/function_wizard_window.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

namespace utilities::windows{
    QRegularExpression FunctionWizard::function =
            QRegularExpression("WS* LN '(' WS* expr WS* ')' WS*");
    QRegularExpression FunctionWizard::var_node =
            QRegularExpression(R"(^[ \t]*VAR\([ \t]*!\(\'[a-zA-Z0-9][^_^\(\)!,;#\' ]+\'\)[ \t]*#[a-zA-Z][a-zA-Z0-9\'\^\*]*[ \t]*\)|[ \t]*#[a-zA-Z][a-zA-Z0-9\'\^\*]*[ \t]*$)");


    FunctionWizard::FunctionWizard(QWidget* parent):QMainWindow(parent){}
    FunctionWizard::FunctionWizard(QString parsed_text_to_function,QWidget* parent):QMainWindow(parent){}
    FunctionWizard::FUNCTION_TYPE FunctionWizard::parse_entry(const QString& text_part){

    }
}
