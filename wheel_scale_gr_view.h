#ifndef WHEELSCALEGRVIEW_H
#define WHEELSCALEGRVIEW_H

#include <QGraphicsView>



class WheelScaleGrView : public QGraphicsView
{ Q_OBJECT
public:
    WheelScaleGrView(QWidget* p = nullptr);

public slots:
    void fitScene(const QRectF &rect);

protected:
    void wheelEvent(QWheelEvent *event) override;

};

#endif // WHEELSCALEGRVIEW_H
