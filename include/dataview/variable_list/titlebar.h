#pragma once
#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QPaintEvent>
#include <QPaintDevice>
#include "utilities/custom_widgets/buttons.h"
#include "kernel/application.h"

namespace dataview{

class TitleBarLabel:public QLabel{
    Q_OBJECT
    Qt::Orientation orientation_ = Qt::Horizontal;
    virtual void paintEvent(QPaintEvent*) override;
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
public:
    TitleBarLabel(QWidget* parent);
    ~TitleBarLabel();
    void set_orientation(Qt::Orientation);
};

class TitleBar:public QFrame, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    TitleBar(QWidget*, Qt::Orientation);
    void __init__();

private:
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;

    TitleBarLabel *label_var_list;
    CollapseButton *collapse_var_list;
    CloseButton *close_var_list;
    Qt::Orientation orientation_;
    QVBoxLayout* vertical_;
    QHBoxLayout* horizontal_;

private slots:
    void collapse();
};
}
