/***************************************************************************************************
**      2019-08-09  HAbstractMultiPanel
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractMultiPanelPrivate;

class HAbstractMultiPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(int count READ count)

public:
    explicit HAbstractMultiPanel(QWidget *parent = nullptr);
    ~HAbstractMultiPanel() override;

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
    virtual bool removeWidget(int index);
    virtual bool removeWidget(QWidget *);

public slots:
    virtual bool setCurrentIndex(int value);
    virtual bool setCurrentWidget(QWidget *);
    virtual bool setWidgetIcon(int index, const QIcon &icon);
    virtual bool setWidgetTitle(int index, const QString &title);

protected:
    HAbstractMultiPanel(HAbstractMultiPanelPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    QScopedPointer<HAbstractMultiPanelPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
