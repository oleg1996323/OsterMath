#pragma once
#include "utilities/custom_widgets/tool_group.h"
#include <PushButton.h>
#include "styles.h"

namespace Book{
namespace Widgets{
namespace toolbar{

class File:public Group{
    Q_OBJECT
public:
    File(QWidget* parent):Group(QObject::tr("File"),parent){
        setObjectName("file_gb");
        {
            new_file = new ToolButton(":booktool/icons/createfile.png",this);
            new_file->setToolTip(QObject::tr("Create new file"));
            new_file->setObjectName("createnewbook");
            grid_layout()->addWidget(new_file,0,0,1,1);
        }
        {
            save_file = new ToolButton(":booktool/icons/savefile.png",this);
            save_file->setToolTip(QObject::tr("Save"));
            save_file->setObjectName("savebook");
            grid_layout()->addWidget(save_file,0,1,1,1);
        }
        {
            save_copy = new ToolButton(":booktool/icons/savecopyfile.png",this);
            save_copy->setToolTip(QObject::tr("Save copy"));
            save_copy->setObjectName("savecopy");
            grid_layout()->addWidget(save_copy,1,0,1,1);
        }

        QWidget* empty = new QWidget(this);
        empty->setFixedSize(new_file->size());
        grid_layout()->addWidget(empty,1,1,1,1);

        empty = new QWidget(this);
        empty->setFixedHeight(new_file->height());
        grid_layout()->addWidget(new QWidget(this),2,0,2,1);

        this->setLayout(grid_layout());
    }
private:
    IconedButton *new_file;
    IconedButton *save_file;
    IconedButton *save_copy;
    IconedButton *print;
};
}}}
