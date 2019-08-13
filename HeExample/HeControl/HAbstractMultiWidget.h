/***************************************************************************************************
**      2019-08-09  HAbstractMultiWidget
***************************************************************************************************/

#ifndef HABSTRACTMULTIWIDGET_H
#define HABSTRACTMULTIWIDGET_H

#include "HControlGlobal.h"
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractMultiWidgetPrivate;

class HAbstractMultiWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(int count READ count)

public:
    explicit HAbstractMultiWidget(QWidget *parent = nullptr);
    ~HAbstractMultiWidget() override;

signals:
    void currentIndexChanged(int);

public:
    virtual int currentIndex() const;
    virtual int count() const = 0;
    virtual int indexOf(QWidget *) const = 0;
    virtual QWidget *widget(int index) const = 0;
    virtual QWidget *currentWidget() const = 0;

public:
    virtual void addWidget(QWidget *widget, const QString &title = QString());
    virtual void addWidget(QWidget *widget, const QIcon &icon, const QString &title = QString());
    virtual void insertWidget(int index, QWidget *widget, const QString &title = QString());
    virtual void insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &title = QString());
    virtual void removeWidget(int index) = 0;
    virtual void removeWidget(QWidget *);

public slots:
    virtual bool setCurrentIndex(int value);
    virtual bool setCurrentWidget(QWidget *);
    virtual bool setWidgetIcon(int index, const QIcon &icon);
    virtual bool setWidgetTitle(int index, const QString &title);

protected:
    HAbstractMultiWidget(HAbstractMultiWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractMultiWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTMULTIWIDGET_H
