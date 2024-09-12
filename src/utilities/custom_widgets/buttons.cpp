#include "utilities/custom_widgets/buttons.h"
#include <QPainterPath>
#include "styles/styles.h"
#include "utilities/paths.h"
#include <QStylePainter>
#include <QStyleOptionButton>

//TODO add namespace utilities and make refactoring
//TODO make individual library for these buttons


CloseButton::CloseButton(const QString& res_path,QWidget* parent):PushButton(parent){
    setContentsMargins(0,0,0,0);
    setFixedSize(20,20);
    QPainterPath path;
    path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
    setIcon(paths::iconFromPath(path,QPixmap(res_path),size(),Qt::transparent));
    setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
}
void CloseButton::paintEvent(QPaintEvent* event){
    PushButton::paintEvent(event);
}

