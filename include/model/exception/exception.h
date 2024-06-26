#pragma once
#include "exception/exception.h"
#include <QMessageBox>

namespace model{
    exceptions::EXCEPTION_TYPE exception_handler(std::function<void()> function,QWidget* caller=nullptr);
}
