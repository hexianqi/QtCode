#include "HFaltStyle_p.h"
#include <QtGui/QColor>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QScrollBar>

HE_CONTROL_BEGIN_NAMESPACE

HFaltStyle::HFaltStyle(QObject *parent) :
    HAbstractCustomStyle(*new HFaltStylePrivate, parent)
{
}

HFaltStyle::HFaltStyle(HFaltStylePrivate &p, QObject *parent) :
    HAbstractCustomStyle(p, parent)
{
}

HFaltStyle::~HFaltStyle()
{
}

QString HFaltStyle::typeName()
{
    return "HFaltStyle";
}

QString HFaltStyle::pushButton(QVariantMap param)
{
    auto p = data("padding", param, 8).toInt();
    auto br = data("border-radius", param, 5).toInt();
    auto c = data("color", param, "#E6F8F5").toString();
    auto b = data("background", param, "#1ABC9C").toString();
    auto h_c = data("hover_color", param, "#FFFFFF").toString();
    auto h_b = data("hover_background", param, "#2EE1C1").toString();
    auto p_c = data("pressed_color", param, "#A7EEE6").toString();
    auto p_b = data("pressed_background", param, "#16A086").toString();

    QStringList list;
    list << QString("QPushButton { border-style:none; padding:%1px; border-radius:%2px; color:%3; background:%4; }").arg(p).arg(br).arg(c).arg(b)
         << QString("QPushButton:hover { color:%1; background:%2; }").arg(h_c).arg(h_b)
         << QString("QPushButton:pressed { color:%1; background:%2; }").arg(p_c).arg(p_b);
    return list.join("\n");
}

QString HFaltStyle::lineEdit(QVariantMap param)
{
    auto p = data("padding", param, 3).toInt();
    auto br = data("border-radius", param, 3).toInt();
    auto bw = data("border-width", param, 2).toInt();
    auto bc = data("border-color", param, "#DCE4EC").toString();
    auto f_bw = data("focus_border-width", param, bw).toInt();
    auto f_sc = data("focus_solid-color", param, "#1ABC9C").toString();

    QStringList list;
    list << QString("QLineEdit { border-style:none; padding:%1px; border-radius:%2px; border:%3px solid %4; }")
            .arg(p).arg(br).arg(bw).arg(bc)
         << QString("QLineEdit:focus { border:%1px solid %2;}")
            .arg(f_bw).arg(f_sc);
    return list.join("\n");
}

QString HFaltStyle::progressBar(QVariantMap param)
{
    auto fs = data("font-size", param, 9).toInt();
    auto br = data("border-radius", param, 5).toInt();
    auto mh = data("max-height", param, 8).toInt();
    auto b = data("background", param, "#E8EDF2").toString();
    auto bc = data("border-color", param, b).toString();
    auto c_br = data("chunk_border-radius", param, br).toInt();
    auto c_b = data("chunk_background", param, "#1ABC9C").toString();

    QStringList list;
    list << QString("QProgressBar { font:%1pt; max-height:%2px; background:%3; border-radius:%4px; text-align:center; border:1px solid %5; }")
            .arg(fs).arg(mh).arg(b).arg(br).arg(bc)
         << QString("QProgressBar:chunk { border-radius:%1px; background-color:%2; }")
            .arg(c_br).arg(c_b);
    return list.join("\n");
}

QString HFaltStyle::slider(QVariantMap param)
{
    auto h = data("height", param, 8).toInt();
    auto br = h / 2;
    auto b = data("background", param, "#E8EDF2").toString();
    auto g_b = data("groove_background", param, "#1ABC9C").toString();
    auto h_b = data("handle_background", param, "#1ABC9C").toString();
    auto h_w = h * 3 / 2 + h / 5;
    auto h_br = h_w / 2;
    auto h_o = h_br / 2;

    QStringList list;
    list << QString("QSlider::groove:horizontal { height:%2px; border-radius:%3px; background:%1; }")
            .arg(b).arg(h).arg(br)
         << QString("QSlider::add-page:horizontal { height:%2px; border-radius:%3px; background:%1;}")
            .arg(b).arg(h).arg(br)
         << QString("QSlider::sub-page:horizontal { height:%2px; border-radius:%3px; background:%1;}")
            .arg(g_b).arg(h).arg(br)
         << QString("QSlider::handle:horizontal { width:%2px; margin-top:-%3px; margin-bottom:-%3px; border-radius:%4px;"
                    "background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF, stop:0.8 %1);}")
                    .arg(h_b).arg(h_w).arg(h_o).arg(h_br);
    list << QString("QSlider::groove:vertical { width:%2px; border-radius:%3px; background:%1; }")
            .arg(b).arg(h).arg(br)
         << QString("QSlider::add-page:vertical { width:%2px; border-radius:%3px; background:%1; }")
            .arg(g_b).arg(h).arg(br)
         << QString("QSlider::sub-page:vertical { width:%2px; border-radius:%3px; background:%1;}")
            .arg(b).arg(h).arg(br)
         << QString("QSlider::handle:vertical { height:%2px; margin-left:-%3px; margin-right:-%3px; border-radius:%4px;"
                    "background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF,stop:0.8 %1);}")
                    .arg(h_b).arg(h_w + 1).arg(h_o).arg(h_br);
    return list.join("\n");
}

QString HFaltStyle::radioButton(QVariantMap param)
{
    auto br = data("indicator_border-radius", param, 8).toInt();
    auto wh = br * 2;
    auto c_b = data("indicator_checked_background", param, "#1ABC9C").toString();
    auto u_b = data("indicator_unchecked_background", param, "#D7DBDE").toString();

    QStringList list;
    list << QString("QRadioButton::indicator { border-radius:%1px; width:%2px; height:%2px; }").arg(br).arg(wh)
         << QString("QRadioButton::indicator::unchecked { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF, stop:0.7 %1); }").arg(u_b)
         << QString("QRadioButton::indicator::checked   { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 %1, stop:0.3 %1, stop:0.4 #FFFFFF, stop:0.6 #FFFFFF, stop:0.7 %1);}").arg(c_b);
    return list.join("\n");
}

QString HFaltStyle::checkBox(QVariantMap param)
{
    auto br = data("indicator_border-radius", param, 3).toInt();
    auto wh = br * 6;
    auto c_b = data("indicator_checked_background", param, "#1ABC9C").toString();
    auto u_b = data("indicator_unchecked_background", param, "#D7DBDE").toString();

    QStringList list;
    list << QString("QCheckBox::indicator { border-radius:%1px; width:%2px; height:%2px; }").arg(br).arg(wh)
         << QString("QCheckBox::indicator::unchecked { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #FFFFFF, stop:0.7 %1); }").arg(u_b)
         << QString("QCheckBox::indicator::checked   { background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 %1, stop:0.3 %1, stop:0.4 #FFFFFF, stop:0.6 #FFFFFF, stop:0.7 %1); }").arg(c_b);
    return list.join("\n");
}

QString HFaltStyle::scrollBar(QVariantMap param)
{
    auto p = data("padding", param, 0).toInt();
    auto br = data("border-radius", param, 6).toInt();
    auto min = data("min", param, 12).toInt();
    auto max = data("max", param, 120).toInt();
    auto b = data("background", param, "#E8EDF2").toString();
    auto h_b = data("handle_background", param, "#1ABC9C").toString();
    auto h_h_b = data("handle_hover_background", param, "#3498DB").toString();
    auto h_p_b = data("handle_pressed_background", param, "#E74C3C").toString();

    QStringList list;
    // handle:指示器
    // add-page:滚动条拉动时增加的部分
    // sub-page:滚动条拉动时减少的部分
    // add-line:递增按钮
    // sub-line:递减按钮
    // 横向滚动条部分
    list << QString("QScrollBar:horizontal { background:%1; padding:%2px; border-radius:%3px; max-height:%4px; }").arg(b).arg(p).arg(br).arg(max)
         << QString("QScrollBar::handle:horizontal { background:%1; min-width:%2px; border-radius:%3px; }").arg(h_b).arg(min).arg(br)
         << QString("QScrollBar::handle:horizontal:hover { background:%1; }").arg(h_h_b)
         << QString("QScrollBar::handle:horizontal:pressed { background:%1; }").arg(h_p_b)
         << QString("QScrollBar::add-page:horizontal { background:none; }")
         << QString("QScrollBar::sub-page:horizontal { background:none; }")
         << QString("QScrollBar::add-line:horizontal { background:none; }")
         << QString("QScrollBar::sub-line:horizontal { background:none; }");
    //纵向滚动条部分
    list << QString("QScrollBar:vertical { background:%1; padding:%2px; border-radius:%3px; max-width:%4px;}").arg(b).arg(p).arg(br).arg(max)
         << QString("QScrollBar::handle:vertical { background:%1; min-height:%2px; border-radius:%3px;} ").arg(h_b).arg(min).arg(br)
         << QString("QScrollBar::handle:vertical:hover { background:%1; }").arg(h_h_b)
         << QString("QScrollBar::handle:vertical:pressed { background:%1; }").arg(h_p_b)
         << QString("QScrollBar::add-page:vertical { background:none; }")
         << QString("QScrollBar::sub-page:vertical { background:none; }")
         << QString("QScrollBar::add-line:vertical { background:none; }")
         << QString("QScrollBar::sub-line:vertical { background:none; }");
    return list.join("\n");
}

void HFaltStyle::setStyle(QPushButton *obj, int padding, int radius, QString normalColor, QString normalBackground, QString hoverColor, QString hoverBackground, QString pressedColor, QString pressedBackground)
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

void HFaltStyle::setStyle(QLineEdit *obj, int padding, int radius, int borderWidth, QString normalColor, QString focusColor)
{
    QVariantMap param;
    param["padding"] = padding;
    param["border-radius"] = radius;
    param["border-width"] = borderWidth;
    param["border-color"] = normalColor;
    param["focus_solid-color"] = focusColor;
    obj->setStyleSheet(lineEdit(param));
}

void HFaltStyle::setStyle(QProgressBar *obj, int fontSize, int height, int radius, QString normalColor, QString chunkColor)
{
    QVariantMap param;
    param["font-size"] = fontSize;
    param["border-radius"] = radius;
    param["max-height"] = height;
    param["background"] = normalColor;
    param["chunk_background"] = chunkColor;
    obj->setStyleSheet(progressBar(param));
}

void HFaltStyle::setStyle(QSlider *obj, int height, QString normalColor, QString grooveColor, QString handleColor)
{
    QVariantMap param;
    param["height"] = height;
    param["background"] = normalColor;
    param["groove_background"] = grooveColor;
    param["handle_background"] = handleColor;
    obj->setStyleSheet(slider(param));
}

void HFaltStyle::setStyle(QRadioButton *obj, int radius, QString uncheckColor, QString checkColor)
{
    QVariantMap param;
    param["indicator_border-radius"] = radius;
    param["indicator_unchecked_background"] = uncheckColor;
    param["indicator_checked_background"] = checkColor;
    obj->setStyleSheet(radioButton(param));
}

void HFaltStyle::setStyle(QCheckBox *obj, int radius, QString uncheckColor, QString checkColor)
{
    QVariantMap param;
    param["indicator_border-radius"] = radius;
    param["indicator_unchecked_background"] = uncheckColor;
    param["indicator_checked_background"] = checkColor;
    obj->setStyleSheet(checkBox(param));
}

void HFaltStyle::setStyle(QScrollBar *obj, int radius, int min, int max, QString background, QString handleNormalColor, QString handleHoverColor, QString handlePressedColor)
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
