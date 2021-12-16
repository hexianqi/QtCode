/***************************************************************************************************
**      2020-09-02  HSeekSlider
**                  参考VLC-3.0.9.2
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QSlider>

HE_BEGIN_NAMESPACE

struct HSeekPoint;
class HSeekSliderPrivate;

class HSeekSlider : public QSlider
{
    Q_OBJECT

public:
    explicit HSeekSlider(Qt::Orientation orientation, bool classic = false, QWidget *parent = nullptr);
    ~HSeekSlider() override;

signals:
    void sliderDragged(double);
    void chapterChanged(int);

public:
    QSize sizeHint() const override;

public:
    void setChapters(QList<HSeekPoint>);

public slots:
    void setPosition(double pos, int length);
    void setSeekable(bool b);
    void setBuffering(double);
    void inputUpdated(bool);
    void hideHandle();

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void hideEvent(QHideEvent *) override;
    bool eventFilter(QObject *, QEvent *) override;

protected:
    void setHandleOpacity(double);
    void setLoading(double);
    void updatePos();
    int handleLength();
    int valueFromPosition(int pos);
    void handleReleasedButton();

protected:
    void init();

protected:
    QScopedPointer<HSeekSliderPrivate> d_ptr;
};

HE_END_NAMESPACE

