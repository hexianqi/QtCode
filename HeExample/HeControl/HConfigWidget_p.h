#ifndef HCONFIGWIDGET_P_H
#define HCONFIGWIDGET_P_H

#include "HConfigWidget.h"
#include "HAbstractMultiWidget_p.h"
#include <QtWidgets/QAbstractItemDelegate>

class QListWidget;
class QLabel;
class QStackedWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HConfigWidgetPrivate : public HAbstractMultiWidgetPrivate
{
public:
    bool discarding = false;
    bool saving = false;
    bool applying = false;
    QListWidget *view;
    QLabel *title;
    QStackedWidget *stack;
};

class HConfigWidgetDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit HConfigWidgetDelegate(QObject *parent = nullptr);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONFIGWIDGET_P_H
