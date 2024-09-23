#include "wheel_scale_gr_view.h"

#include <QWheelEvent>
#include <QtMath>

namespace
{
constexpr qreal ZoomSpeed = 1.2;
}

WheelScaleGrView::WheelScaleGrView(QWidget *p) :
    QGraphicsView(p)
{}

void WheelScaleGrView::fitScene(const QRectF &rect)
{
    fitInView(rect, Qt::KeepAspectRatio);
}

void WheelScaleGrView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = event->delta() > 0 ? ZoomSpeed : 1/ZoomSpeed;
    scale(scaleFactor,scaleFactor);
}
