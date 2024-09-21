#pragma once
#include <QWidget>
#include <PushLabel.h>
#include "kernel/def.h"
#include <QSignalMapper>

struct INFO_NODE;
class QHBoxLayout;
namespace dataview{
namespace utilities{
class LinkButton:public PushLabel{
    Q_OBJECT
public:
    LinkButton(QString,QWidget*);
    int get_pos() const;
    void set_pos(int pos);
private:
    int pos_ = -1;
};
}

class LinkViewedNodes:public QWidget,public ObjectFromSettings,public Retranslatable{
    Q_OBJECT
public:
    LinkViewedNodes(QWidget* parent);
    void reset();
signals:
    void update_sequence(std::vector<INFO_NODE>);
public slots:
    void add_button(INFO_NODE);
private:
    virtual void __retranslate__() override;
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_language__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;


private slots:
    void activated_button(const QString&);
private:
    void __add_button__(const QString&, INFO_NODE);
    std::vector<utilities::LinkButton*> sequence_button_;
    std::vector<INFO_NODE> sequence_info_;
    QHBoxLayout* layout_;
};

}
