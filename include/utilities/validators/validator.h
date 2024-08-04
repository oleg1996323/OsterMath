#pragma once
#include <QRegularExpression>
#include <QValidator>

namespace validator{

enum STATE{
    Acceptable,
    Invalid
};

class DataPool:public QRegularExpression{
public:
    static STATE validate(const QString& str){
        if (str.contains(QRegularExpression("[a-zA-Z0-9_] (~[()!,;#' ])*"))) {
            return Invalid;
        }
        return Acceptable;
    }
};

class BaseData{
public:
    static STATE validate(const QString& str){
        if (str.contains(QRegularExpression("[a-zA-Z0-9_] (~[()!,;#' ])*"))) {
            return Invalid;
        }
        return Acceptable;
    }
};

class Variable{
public:
    static STATE validate(const QString& str){
        if (str.contains(QRegularExpression("[a-zA-Z] ((\' | *) | [a-zA-Z0-9])*"))) {
            return Invalid;
        }
        return Acceptable;
    }
};

}
