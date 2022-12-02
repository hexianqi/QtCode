/***************************************************************************************************
**      2022-11-28  HPatternLockWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HPatternLockWidgetPrivate;

class HPatternLockWidget : public QWidget
{
    Q_OBJECT

public:
    enum CircularState
    {
        Normal,
        Hover
    };

    enum PatternLockState
    {
        NotSet,
        Setting,
        Valid,
        Invalid
    };

public:
    explicit HPatternLockWidget(int number, QWidget *parent = nullptr);
    ~HPatternLockWidget() override;

signals:
    void passwordChanged(QString);

public:
    int number() const;
    QString password();
    void setNumber(int);
    void reset();

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private:
    void onHoverTimer();

protected:
    QScopedPointer<HPatternLockWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
