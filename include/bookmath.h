#ifndef BOOKMATH_H
#define BOOKMATH_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BookMath; }
QT_END_NAMESPACE

class BookMath : public QMainWindow
{
    Q_OBJECT

public:
    BookMath(QWidget *parent = nullptr);
    ~BookMath();

private:
    Ui::BookMath *ui;
};
#endif // BOOKMATH_H
