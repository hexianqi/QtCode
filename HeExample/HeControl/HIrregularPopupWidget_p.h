#pragma once

#include "HIrregularPopupWidget.h"

HE_BEGIN_NAMESPACE

class HIrregularPopupWidgetPrivate
{
public:
    HIrregularPopupWidget::SharpPosition sharpPosition{HIrregularPopupWidget::Left};
    int SharpWidth{30};
    int SharpHeight{30};
    QColor backgroundColor{"#31305a"};
    QString text;
};

HE_END_NAMESPACE

