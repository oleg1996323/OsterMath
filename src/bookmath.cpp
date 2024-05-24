#include "bookmath.h"
#include "./ui_bookmath.h"
#include "./ui_var_list.h"

BookMath::BookMath(QObject *parent)
    : QMainWindow(parent)
    , ui(new Ui::BookMath),
      sets_()
{
    ui->setupUi(this);
}

BookMath::~BookMath()
{
    delete ui;
}

