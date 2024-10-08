#pragma once
#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QPaintEvent>
#include <QPaintDevice>
#include "CollapsibleButton.h"
#include "kernel/def.h"

namespace dataview{

class TitleBarLabel:public QLabel{
    Q_OBJECT

    const int separation_between_btns_and_label_ = 20;
    mutable Qt::Orientation orientation_ = Qt::Horizontal;
public:
    TitleBarLabel(QWidget* parent);
    ~TitleBarLabel();
    void set_orientation(Qt::Orientation);
    virtual void paintEvent(QPaintEvent*) override;
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
};

class TitleBar:public QWidget, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    TitleBar(QWidget*, Qt::Orientation);
    void __init__();
    virtual void paintEvent(QPaintEvent*) override;
    virtual QSize sizeHint() const override;
private:
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
    virtual bool event(QEvent*) override;

    TitleBarLabel *label_var_list;
    CollapseButton *collapse_var_list;
    IconedButton *close_var_list;
    Qt::Orientation orientation_;
    QVBoxLayout* vertical_;
    QHBoxLayout* horizontal_;

private slots:
    void collapse();
};
}
