/***************************************************************************************************
**      2019-08-06  HListNavigator
***************************************************************************************************/

#ifndef HLISTNAVIGATOR_H
#define HLISTNAVIGATOR_H

#include "HControlGlobal.h"
#include <QtWidgets/QAbstractSlider>

class QListWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HListNavigatorPrivate;

class HListNavigator : public QAbstractSlider
{
    Q_OBJECT
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(bool autoRaise READ isAutoRaise WRITE setAutoRaise)
    Q_PROPERTY(Qt::ToolButtonStyle toolButtonStyle READ toolButtonStyle WRITE setToolButtonStyle)

public:
    explicit HListNavigator(QWidget *parent = nullptr);
    ~HListNavigator() override;

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
    HListNavigator(HListNavigatorPrivate &p, QWidget *parent = nullptr);

protected:
    void sliderChange(SliderChange change) override;
    void updateUi(int value);
    void updateRange();

protected:
    QScopedPointer<HListNavigatorPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HLISTNAVIGATOR_H
