#ifndef HTIPWIDGET_P_H
#define HTIPWIDGET_P_H

#include "HTipWidget.h"
#include <QtCore/QPersistentModelIndex>

class QStringListModel;
class QVBoxLayout;
class QLabel;
class QCheckBox;
class QPushButton;

HE_CONTROL_BEGIN_NAMESPACE

class HTipWidgetPrivate
{
public:
    QIcon defaultIcon;
    QSize iconSize;
    QPersistentModelIndex currentTip;
    QStringListModel *model;
    QVBoxLayout *layout;
    QWidget *headerWidget;
    QLabel *label;
    QTextBrowser *browser;
    QCheckBox *check;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *closeButton;
};

HE_CONTROL_END_NAMESPACE

#endif // HTIPWIDGET_P_H
