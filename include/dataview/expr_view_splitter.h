#pragma once
#include <QSplitter>
#include <QObject>
#include "dataview/sheets.h"
#include "dataview/expression_view.h"
#include "kernel/def.h"

namespace dataview{

class OverlayHandleVisualEffect:public QWidget{
    Q_OBJECT
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE set_orientation NOTIFY orientation_changed)
    Q_PROPERTY(QWidget* effect_parent READ get_effect_parent WRITE set_effect_parent)
public:
    OverlayHandleVisualEffect(QWidget* parent_drawed_on, QWidget* eff_parent, QSize size, Qt::Orientation orientation);

    virtual void paintEvent(QPaintEvent *event) override;

    virtual void moveEvent(QMoveEvent* event) override{
        QWidget::moveEvent(event);
    }

    virtual void showEvent(QShowEvent* event) override{
        QWidget::showEvent(event);
        raise();
    }

    Qt::Orientation orientation() const{
        return orientation_;
    }
    void set_orientation(Qt::Orientation o){
        orientation_ = o;
    }

    QWidget* get_effect_parent() const{
        return effect_parent;
    }

    void set_effect_parent(QWidget* p){
        effect_parent = p;
    }

signals:
    void orientation_changed();

private:
    Qt::Orientation orientation_;
    QWidget* effect_parent;
};

class SplitterHandle:public QSplitterHandle{
    Q_OBJECT
public:
    SplitterHandle(Qt::Orientation orientation, QSplitter *parent):QSplitterHandle(orientation,parent){
        set_effects(new OverlayHandleVisualEffect(parent,this,{width(),height()*10},orientation));
    }

    virtual void paintEvent(QPaintEvent* event) override;
    virtual void showEvent(QShowEvent* event) override;
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void moveEvent(QMoveEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

    void set_effects(OverlayHandleVisualEffect*);
private:
    std::unique_ptr<OverlayHandleVisualEffect> effects_;
};

class DataViewSplit:public QSplitter, public ObjectFromSettings{
    Q_OBJECT
public:
    DataViewSplit(QWidget* parent);

    Sheets* sheets() const;
    virtual void paintEvent(QPaintEvent* event) override;
private:

    void __define_view__();

    void __define_signals_slots__();

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;

    virtual QSplitterHandle* createHandle() override;
    Sheets* sheets_;
    VarExpressionView* expression_view_;
};
}
