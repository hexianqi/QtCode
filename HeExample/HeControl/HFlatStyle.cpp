#include "HFlatStyle_p.h"
#include <QtGui/QColor>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QScrollBar>

HE_CONTROL_BEGIN_NAMESPACE

HFlatStyle::HFlatStyle(QObject *parent) :
    HAbstractCustomStyle(*new HFlatStylePrivate, parent)
{
}

HFlatStyle::HFlatStyle(HFlatStylePrivate &p, QObject *parent) :
    HAbstractCustomStyle(p, parent)
{
}

HFlatStyle::~HFlatStyle()
{
}

QString HFlatStyle::typeName()
{
    return "HFlatStyle";
}

QString HFlatStyle::pushButton(QVariantMap param)
{
    auto padding = data("padding", param, 8).toInt();
    auto borderRadius = data("border-radius", param, 5).toInt();
    auto color = data("color", param, "#E6F8F5").toString();
    auto background = data("background", param, "#1ABC9C").toString();
    auto hoverColor = data("hover_color", param, "#FFFFFF").toString();
    auto hoverBackground = data("hover_background", param, "#2EE1C1").toString();
    auto pressedColor = data("pressed_color", param, "#A7EEE6").toString();
    auto pressedBackground = data("pressed_background", param, "#16A086").toString();

    QStringList list;
    list << QString("QPushButton { border-style:none; padding:%1px; border-radius:%2px; color:%3; background:%4; }").arg(padding).arg(borderRadius).arg(color).arg(background)
         << QString("QPushButton:hover { color:%1; background:%2; }").arg(hoverColor).arg(hoverBackground)
         << QString("QPushButton:pressed { color:%1; background:%2; }").arg(pressedColor).arg(pressedBackground);
    return list.join("\n");
}

QString HFlatStyle::lineEdit(QVariantMap param)
{
    auto padding = data("padding", param, 3).toInt();
    auto borderRadius = data("border-radius", param, 3).toInt();
    auto borderWidth = data("border-width", param, 2).toInt();
    auto borderColor = data("border-color", param, "#DCE4EC").toString();
    auto focusBorderWidth = data("focus_border-width", param, borderWidth).toInt();
    auto focusSolidColor = data("focus_solid-color", param, "#1ABC9C").toString();

    QStringList list;
    list << QString("QLineEdit { border-style:none; padding:%1px; border-radius:%2px; border:%3px solid %4; }")
            .arg(padding).arg(borderRadius).arg(borderWidth).arg(borderColor)
         << QString("QLineEdit:focus { border:%1px solid %2;}")
            .arg(focusBorderWidth).arg(focusSolidColor);
    return list.join("\n");
}

QString HFlatStyle::progressBar(QVariantMap param)
{
    auto fontSize = data("font-size", param, 9).toInt();
    auto borderRadius = data("border-radius", param, 5).toInt();
    auto maxHeight = data("max-height", param, 8).toInt();
    auto background = data("background", param, "#E8EDF2").toString();
    auto borderColor = data("border-color", param, background).toString();
    auto chunkBorderRadius = data("chunk_border-radius", param, borderRadius).toInt();
    auto chunkBackground = data("chunk_background", param, "#1ABC9C").toString();

    QStringList list;
    list << QString("QProgressBar { font:%1pt; max-height:%2px; background:%3; border-radius:%4px; text-align:center; border:1px solid %5; }")
            .arg(fontSize).arg(maxHeight).arg(background).arg(borderRadius).arg(borderColor)
         << QString("QProgressBar:chunk { border-radius:%1px; background-color:%2; }")
            .arg(chunkBorderRadius).arg(chunkBackground);
    return list.join("\n");
}

QString HFlatStyle::slider(QVariantMap param)
{
    auto height = data("height", param, 8).toInt();
    auto borderRadius = height / 2;
    auto background = data("background", param, "#E8EDF2").toString();
    auto grooveBackground = data("groove_background", param, "#1ABC9C").toString();
    auto handleBackground = data("handle_background", param, "#1ABC9C").toString();
    auto handleWidth = height * 3 / 2 + height / 5;
    auto handleBorderRadius = handleWidth / 2;
    auto handleMargin = handleBorderRadius / 2;

    QStringList list;
    list << QString("QSlider::groove:horizontal { height:%2px; border-radius:%3px; background:%1; }")
            .arg(background).arg(height).arg(borderRadius)
         << QString("QSlider::add-page:horizontal { height:%2px; border-radius:%3px; background:%1;}")
            .arg(background).arg(height).arg(borderRadius)
         << QString("QSlider::sub-page:horizontal { height:%2px; border-radius:%3px; background:%1;}")
            .arg(grooveBackground).arg(height).arg(borderRadius)
         << QString("QSlider::handle:horizontal { width:%2px; margin-top:-%3px; margin-bottom:-%3px; border-radius:%4px;"
                    "background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF, stop:0.8 %1);}")
                    .arg(handleBackground).arg(handleWidth).arg(handleMargin).arg(handleBorderRadius);
    list << QString("QSlider::groove:vertical { width:%2px; border-radius:%3px; background:%1; }")
            .arg(background).arg(height).arg(borderRadius)
         << QString("QSlider::add-page:vertical { width:%2px; border-radius:%3px; background:%1; }")
            .arg(grooveBackground).arg(height).arg(borderRadius)
         << QString("QSlider::sub-page:vertical { width:%2px; border-radius:%3px; background:%1;}")
            .arg(background).arg(height).arg(borderRadius)
         << QString("QSlider::handle:vertical { height:%2px; margin-left:-%3px; margin-right:-%3px; border-radius:%4px;"
                    "background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF,stop:0.8 %1);}")
                    .arg(handleBackground).arg(handleWidth + 1).arg(handleMargin).arg(handleBorderRadius);
    return list.join("\n");
}

QString HFlatStyle::radioButton(QVariantMap param)
{
    auto borderRadius = data("indicator_border-radius", param, 8).toInt();
    auto size = borderRadius * 2;
    auto checkedBackground = data("indicator_checked_background", param, "#1ABC9C").toString();
    auto uncheckedBackground = data("indicator_unchecked_background", param, "#D7DBDE").toString();

    QStringList list;
    list << QString("QRadioButton::indicator { border-radius:%1px; width:%2px; height:%2px; }").arg(borderRadius).arg(size)
         << QString("QRadioButton::indicator::unchecked { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF, stop:0.7 %1); }").arg(uncheckedBackground)
         << QString("QRadioButton::indicator::checked   { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 %1, stop:0.3 %1, stop:0.4 #FFFFFF, stop:0.6 #FFFFFF, stop:0.7 %1);}").arg(checkedBackground);
    return list.join("\n");
}

QString HFlatStyle::checkBox(QVariantMap param)
{
    auto borderRadius = data("indicator_border-radius", param, 3).toInt();
    auto size = borderRadius * 6;
    auto checkedBackground = data("indicator_checked_background", param, "#1ABC9C").toString();
    auto uncheckedBackground = data("indicator_unchecked_background", param, "#D7DBDE").toString();

    QStringList list;
    list << QString("QCheckBox::indicator { border-radius:%1px; width:%2px; height:%2px; }").arg(borderRadius).arg(size)
         << QString("QCheckBox::indicator::unchecked { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF, stop:0.7 %1); }").arg(uncheckedBackground)
         << QString("QCheckBox::indicator::checked   { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 %1, stop:0.3 %1, stop:0.4 #FFFFFF, stop:0.6 #FFFFFF, stop:0.7 %1); }").arg(checkedBackground);
    return list.join("\n");
}

QString HFlatStyle::scrollBar(QVariantMap param)
{
    auto padding = data("padding", param, 0).toInt();
    auto borderRadius = data("border-radius", param, 6).toInt();
    auto min = data("min", param, 12).toInt();
    auto max = data("max", param, 120).toInt();
    auto background = data("background", param, "#E8EDF2").toString();
    auto handleBackground = data("handle_background", param, "#1ABC9C").toString();
    auto handleHoverBackground = data("handle_hover_background", param, "#3498DB").toString();
    auto handlePressedBackground = data("handle_pressed_background", param, "#E74C3C").toString();

    QStringList list;
    // handle:指示器
    // add-page:滚动条拉动时增加的部分
    // sub-page:滚动条拉动时减少的部分
    // add-line:递增按钮
    // sub-line:递减按钮
    // 横向滚动条部分
    list << QString("QScrollBar:horizontal { background:%1; padding:%2px; border-radius:%3px; max-height:%4px; }").arg(background).arg(padding).arg(borderRadius).arg(max)
         << QString("QScrollBar::handle:horizontal { background:%1; min-width:%2px; border-radius:%3px; }").arg(handleBackground).arg(min).arg(borderRadius)
         << QString("QScrollBar::handle:horizontal:hover { background:%1; }").arg(handleHoverBackground)
         << QString("QScrollBar::handle:horizontal:pressed { background:%1; }").arg(handlePressedBackground)
         << QString("QScrollBar::add-page:horizontal { background:none; }")
         << QString("QScrollBar::sub-page:horizontal { background:none; }")
         << QString("QScrollBar::add-line:horizontal { background:none; }")
         << QString("QScrollBar::sub-line:horizontal { background:none; }");
    //纵向滚动条部分
    list << QString("QScrollBar:vertical { background:%1; padding:%2px; border-radius:%3px; max-width:%4px;}").arg(background).arg(padding).arg(borderRadius).arg(max)
         << QString("QScrollBar::handle:vertical { background:%1; min-height:%2px; border-radius:%3px;} ").arg(handleBackground).arg(min).arg(borderRadius)
         << QString("QScrollBar::handle:vertical:hover { background:%1; }").arg(handleHoverBackground)
         << QString("QScrollBar::handle:vertical:pressed { background:%1; }").arg(handlePressedBackground)
         << QString("QScrollBar::add-page:vertical { background:none; }")
         << QString("QScrollBar::sub-page:vertical { background:none; }")
         << QString("QScrollBar::add-line:vertical { background:none; }")
         << QString("QScrollBar::sub-line:vertical { background:none; }");
    return list.join("\n");
}

void HFlatStyle::setStyle(QPushButton *obj, int padding, int radius, QString normalColor, QString normalBackground, QString hoverColor, QString hoverBackground, QString pressedColor, QString pressedBackground)
{
    QVariantMap param;
    param["padding"] = padding;
    param["border-radius"] = radius;
    param["color"] = normalColor;
    param["background"] = normalBackground;
    param["hover_color"] = hoverColor;
    param["hover_background"] = hoverBackground;
    param["pressed_color"] = pressedColor;
    param["pressed_background"] = pressedBackground;
    obj->setStyleSheet(pushButton(param));
}

void HFlatStyle::setStyle(QLineEdit *obj, int padding, int radius, int borderWidth, QString normalColor, QString focusColor)
{
    QVariantMap param;
    param["padding"] = padding;
    param["border-radius"] = radius;
    param["border-width"] = borderWidth;
    param["border-color"] = normalColor;
    param["focus_solid-color"] = focusColor;
    obj->setStyleSheet(lineEdit(param));
}

void HFlatStyle::setStyle(QProgressBar *obj, int fontSize, int height, int radius, QString normalColor, QString chunkColor)
{
    QVariantMap param;
    param["font-size"] = fontSize;
    param["border-radius"] = radius;
    param["max-height"] = height;
    param["background"] = normalColor;
    param["chunk_background"] = chunkColor;
    obj->setStyleSheet(progressBar(param));
}

void HFlatStyle::setStyle(QSlider *obj, int height, QString normalColor, QString grooveColor, QString handleColor)
{
    QVariantMap param;
    param["height"] = height;
    param["background"] = normalColor;
    param["groove_background"] = grooveColor;
    param["handle_background"] = handleColor;
    obj->setStyleSheet(slider(param));
}

void HFlatStyle::setStyle(QRadioButton *obj, int radius, QString uncheckColor, QString checkColor)
{
    QVariantMap param;
    param["indicator_border-radius"] = radius;
    param["indicator_unchecked_background"] = uncheckColor;
    param["indicator_checked_background"] = checkColor;
    obj->setStyleSheet(radioButton(param));
}

void HFlatStyle::setStyle(QCheckBox *obj, int radius, QString uncheckColor, QString checkColor)
{
    QVariantMap param;
    param["indicator_border-radius"] = radius;
    param["indicator_unchecked_background"] = uncheckColor;
    param["indicator_checked_background"] = checkColor;
    obj->setStyleSheet(checkBox(param));
}

void HFlatStyle::setStyle(QScrollBar *obj, int radius, int min, int max, QString background, QString handleNormalColor, QString handleHoverColor, QString handlePressedColor)
{
    QVariantMap param;
    param["border-radius"] = radius;
    param["min"] = min;
    param["max"] = max;
    param["background"] = background;
    param["handle_background"] = handleNormalColor;
    param["handle_hover_background"] = handleHoverColor;
    param["handle_pressed_background"] = handlePressedColor;
    obj->setStyleSheet(scrollBar(param));
}

HE_CONTROL_END_NAMESPACE
