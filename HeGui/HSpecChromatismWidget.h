/***************************************************************************************************
**      2019-05-21  HSpecChromatismWidget 光谱色容差窗体。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include <QtWidgets/QWidget>

HE_GUI_BEGIN_NAMESPACE

class HSpecChromatismWidgetPrivate;

class HE_GUI_EXPORT HSpecChromatismWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSpecChromatismWidget(QWidget *parent = nullptr);
    ~HSpecChromatismWidget() override;

public:
    void initMenuShow();
    void refreshWidget();

protected:
    HSpecChromatismWidget(HSpecChromatismWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void showChromatism(QAction *);

protected:
    QScopedPointer<HSpecChromatismWidgetPrivate> d_ptr;

private:
    void init();
};

HE_GUI_END_NAMESPACE
