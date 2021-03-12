/***************************************************************************************************
**      2019-08-09  HTaskWidget
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HTaskWidgetPrivate;

class HTaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HTaskWidget(QWidget *body, QWidget *parent = nullptr);
    ~HTaskWidget() override;

signals:
    void opened();
    void closed();

public:
    QWidget *body() const;

public slots:
    void setOpen(bool b);
    void setName(const QString &);
    void setIcon(const QIcon &);
    void setToggleIcon(const QIcon &);

protected:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    QScopedPointer<HTaskWidgetPrivate> d_ptr;

private:
    void init(QWidget *body);
    void animate(int);
    void animateFinished();
};

HE_CONTROL_END_NAMESPACE
