#include "utilities/paths.h"
#include <QPainter>
#include <QDebug>

namespace paths{
QPainterPath semiRoundedRect(RectSide side, const QRect& rect, int rounding = 0){
    QPainterPath path;
    switch (side){
    case TOP:{
        path.moveTo(rect.left()+rounding/2,rect.top());
        path.lineTo(rect.right()-rounding,rect.top());
        path.arcTo(QRect(path.currentPosition().toPoint(), QSize(rounding, rounding)), 90, -90);
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.left(),rect.top()+rounding);
        path.arcTo(QRect(path.currentPosition().toPoint(), QSize(rounding, -rounding)), 180, 90);
        break;
    }
        //TODO: testing other cases
    case RIGHT:{
        path.lineTo(rect.right()-rounding,rect.top());
        path.arcTo(QRect(path.currentPosition().toPoint(), QSize(-rounding, rounding)), 90, -90);
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.left(),rect.top()+rounding);
        path.arcTo(QRect(path.currentPosition().toPoint(), QSize(rounding, rounding)), 180, 90);
        break;
    }
    case LEFT:{
        break;
    }
    case BOTTOM:{
        break;
    }
    }
    return path;
}

QPainterPath semiRoundedRect(RectSide side, const QRectF& rect, int rounding = 0){
    QPainterPath path;
    path.moveTo(rect.left()+rounding/2,rect.top());
    path.lineTo(rect.right()-rounding,rect.top());
    path.arcTo(QRect(path.currentPosition().toPoint(), QSize(rounding, rounding)), 90, -90);
    path.lineTo(rect.bottomRight());
    path.lineTo(rect.bottomLeft());
    path.lineTo(rect.left(),rect.top()+rounding);
    path.arcTo(QRect(path.currentPosition().toPoint(), QSize(rounding, -rounding)), 180, 90);
    return path;
}
}
