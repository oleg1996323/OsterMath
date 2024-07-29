#pragma once
#include "utilities/custom_widgets/tool_group.h"
#include "utilities/custom_widgets/buttons.h"

namespace Book{
namespace Widgets{
namespace toolbar{

class Export:public Group{
    Q_OBJECT
public:
    Export(QWidget* parent):Group(QObject::tr("Export"),parent){
        setObjectName("export_gb");
        {
            to_excel = new ToolButton(":booktool/icons/convertexcel.png",this);
            to_excel->setToolTip(QObject::tr("Export to Excel"));
            to_excel->setObjectName("to_excel");
            grid_layout()->addWidget(to_excel,0,0,1,1);
        }
        {
            to_word = new ToolButton(":booktool/icons/convertpdf.png",this);
            to_word->setToolTip(QObject::tr("Export to Word"));
            to_word->setObjectName("to_word");
            grid_layout()->addWidget(to_word,0,1,1,1);
        }
        {
            to_pdf = new ToolButton(":booktool/icons/convertword.png",this);
            to_pdf->setToolTip(QObject::tr("Export to PDF"));
            to_pdf->setObjectName("to_pdf");
            grid_layout()->addWidget(to_pdf,1,0,1,1);
        }
        {
            to_image = new ToolButton(":booktool/icons/convertimage.png",this);
            to_image->setToolTip(QObject::tr("Export to image"));
            to_image->setObjectName("to_image");
            grid_layout()->addWidget(to_image,1,1,1,1);
        }

        QWidget* empty = new QWidget(this);
        empty->setMaximumHeight(to_excel->height());
        grid_layout()->addWidget(new QWidget(this),2,0,2,1);

    }
private:
    ToolButton *to_excel;
    ToolButton *to_word;
    ToolButton *to_pdf;
    ToolButton *to_image;
};
}}}
