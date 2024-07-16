#pragma once
#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include "utilities/custom_widgets/buttons.h"
#include "kernel/application.h"

namespace dataview{

class TitleBar:public QFrame, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    TitleBar(QWidget*, Qt::Orientation);

    void setVertical();
    void setHorizontal();

private:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;

    class Label:public QLabel{
    public:
        Label(QWidget* parent);
        ~Label();
    };

    QLayout* common_layout_;
    Label *label_var_list;
    CollapseButton *collapse_var_list;
    CloseButton *close_var_list;
    Qt::Orientation orientation_;
};
}
