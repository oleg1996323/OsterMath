#pragma once

#include <QMainWindow>
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BookMath; }
QT_END_NAMESPACE

class BookMath : public QMainWindow
{
    Q_OBJECT

public:
    BookMath(QObject *parent = nullptr);
    ~BookMath();

private:
    Ui::BookMath *ui;
    GlobalSettings sets_;
};
