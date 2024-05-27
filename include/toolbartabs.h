#pragma once
#include <QTabWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStyle>
#include <QCommonStyle>
#include <QPainter>
#include <QPixmap>
#include "styles.h"
#include "utilities/custom_widgets/buttons.h"

class BookToolGroup:public QGroupBox{
public:
    BookToolGroup(const QString& title,QWidget* parent):QGroupBox(title,parent){
        setAlignment(Qt::AlignmentFlag::AlignHCenter);
        setContentsMargins(0,0,0,0);
        setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
        layout_ = new QGridLayout(this);
    }

    QGridLayout* grid_layout(){
        return layout_;
    }
private:
    QGridLayout* layout_;
};

class FileBox:public BookToolGroup{
    Q_OBJECT
public:
    FileBox(QWidget* parent):BookToolGroup(QObject::tr("Файл"),parent){
        setObjectName("file_gb");
        {
            new_file = new ToolButton(":booktool/icons/createfile.png",this);
            new_file->setToolTip("Создать новый файл");
            new_file->setObjectName("createnewbook");
            grid_layout()->addWidget(new_file,0,0,1,1);
        }
        {
            save_file = new ToolButton(":booktool/icons/savefile.png",this);
            save_file->setToolTip("Сохранить");
            save_file->setObjectName("savebook");
            grid_layout()->addWidget(save_file,0,1,1,1);
        }
        {
            save_copy = new ToolButton(":booktool/icons/savecopyfile.png",this);
            save_copy->setToolTip("Сохранить в копию");
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
    ToolButton *new_file;
    ToolButton *save_file;
    ToolButton *save_copy;
    ToolButton *print;
};

class ExportBox:public BookToolGroup{
    Q_OBJECT
public:
    ExportBox(QWidget* parent):BookToolGroup("Экспорт",parent){
        setObjectName("export_gb");
        {
            to_excel = new ToolButton(":booktool/icons/convertexcel.png",this);
            to_excel->setToolTip("Экспорт в Excel");
            to_excel->setObjectName("to_excel");
            grid_layout()->addWidget(to_excel,0,0,1,1);
        }
        {
            to_word = new ToolButton(":booktool/icons/convertpdf.png",this);
            to_word->setToolTip("Экспорт в Word");
            to_word->setObjectName("to_word");
            grid_layout()->addWidget(to_word,0,1,1,1);
        }
        {
            to_pdf = new ToolButton(":booktool/icons/convertword.png",this);
            to_pdf->setToolTip("Экспорт в PDF");
            to_pdf->setObjectName("to_pdf");
            grid_layout()->addWidget(to_pdf,1,0,1,1);
        }
        {
            to_image = new ToolButton(":booktool/icons/convertimage.png",this);
            to_image->setToolTip("Экспорт в изображение");
            to_image->setObjectName("to_image");
            grid_layout()->addWidget(to_image,1,1,1,1);
        }

        QWidget* empty = new QWidget(this);
        empty->setMaximumHeight(to_excel->height());
        grid_layout()->addWidget(new QWidget(this),2,0,2,1);

        //this->setLayout(layout);

    }
private:
    ToolButton *to_excel;
    ToolButton *to_word;
    ToolButton *to_pdf;
    ToolButton *to_image;
};

class BookTools:public QTabWidget{
public:
    BookTools(QWidget* parent):QTabWidget(parent){
        setContentsMargins(0,0,0,0);
        {
            QHBoxLayout* layout;
            QSpacerItem* spacer = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Minimum);
            layout = new QHBoxLayout(this);
            layout->setContentsMargins(5,5,5,5);
            file_widget = new QWidget(this);
            file_box = new FileBox(this);
            export_box = new ExportBox(this);

            layout->addWidget(file_box);
            layout->addWidget(export_box);
            layout->addItem(spacer);
            file_widget->setLayout(layout);
        }
        {
//            insert_widget = new QWidget(this);
//            QHBoxLayout* layout;
//            layout = new QHBoxLayout(this);

        }
        this->addTab(file_widget,"Файл");

    }
private:
    QWidget *file_widget;
    QWidget *insert_widget;
    QWidget *format_widget;
    FileBox* file_box;
    ExportBox* export_box;
};
