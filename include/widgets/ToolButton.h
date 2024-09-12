#pragma once
#include "PushButton.h"

class ToolButton:public PushButton{
    Q_OBJECT
public:
    ToolButton(const QString& res_path,QWidget* parent);
};
