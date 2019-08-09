/***************************************************************************************************
**      2019-08-02  HConfigWidget
***************************************************************************************************/

#ifndef HCONFIGWIDGET_H
#define HCONFIGWIDGET_H

#include "HAbstractMultiWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HConfigWidgetPrivate;

class HConfigWidget : public HAbstractMultiWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HConfigWidget)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)

public:
    explicit HConfigWidget(QWidget *parent = nullptr);
    ~HConfigWidget() override;

signals:
    void saving();
    void applying(int);
    void discarding(int);

public:    
    int count() const override;
    int indexOf(QWidget *) const override;
    QWidget *widget(int index) const override;
    QWidget *currentWidget() const override;
    QSize iconSize() const;

public:
    void insertWidget(int index, QWidget *widget, const QIcon &icon = QIcon(), const QString &label = QString()) override;
    void removeWidget(int index) override;

public slots:
    bool setCurrentIndex(int value) override;
    bool setWidgetIcon(int index, const QIcon &icon) override;
    bool setWidgetTitle(int index, const QString &title) override;
    void setIconSize(const QSize &);
    void save();
    void apply();
    void discard();

protected:
    HConfigWidget(HConfigWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HCONFIGWIDGET_H
