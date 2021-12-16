#pragma once

#include "HTipWidget.h"
#include <QtCore/QPersistentModelIndex>

class QStringListModel;
class QVBoxLayout;
class QLabel;
class QCheckBox;
class QPushButton;

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
