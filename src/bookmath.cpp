#include "bookmath.h"
#include "./ui_bookmath.h"

BookMath::BookMath(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BookMath)
{
    ui->setupUi(this);
}

BookMath::~BookMath()
{
    delete ui;
}

