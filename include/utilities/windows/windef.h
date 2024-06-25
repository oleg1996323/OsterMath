#pragma once
#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QStringList>
#include <QList>
#include "kernel/def.h"

enum class SUBWINDOWTYPES{
    CREATE,
    OPEN,
    SAVEAS
};

class AbstractSubWindowInterface{
public:
    virtual ~AbstractSubWindowInterface(){}

    virtual SUBWINDOWTYPES type() const = 0;
protected:

};
