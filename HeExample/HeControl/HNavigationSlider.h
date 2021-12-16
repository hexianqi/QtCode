/***************************************************************************************************
**      2019-08-06  HNavigationSlider
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QAbstractSlider>

class QListWidget;

HE_BEGIN_NAMESPACE

class HNavigationSliderPrivate;

class HNavigationSlider : public QAbstractSlider
{
    Q_OBJECT
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(bool autoRaise READ isAutoRaise WRITE setAutoRaise)
    Q_PROPERTY(Qt::ToolButtonStyle toolButtonStyle READ toolButtonStyle WRITE setToolButtonStyle)

public:
    explicit HNavigationSlider(QWidget *parent = nullptr);
    ~HNavigationSlider() override;

signals:
    void first();
    void previous();
    void next();
    void last();

public:
    bool isAutoRaise() const;
    Qt::ToolButtonStyle toolButtonStyle() const;

public slots:
    void setOrientation(Qt::Orientation value);
    void setAutoRaise(bool b);
    void setToolButtonStyle(Qt::ToolButtonStyle value);
    void setListWidget(QListWidget *);
    void toFirst();
    void toPrevious();
    void toNext();
    void toLast();

protected:
    HNavigationSlider(HNavigationSliderPrivate &p, QWidget *parent = nullptr);

protected:
    void sliderChange(SliderChange change) override;
    void updateUi(int value);
    void updateRange();

protected:
    QScopedPointer<HNavigationSliderPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
