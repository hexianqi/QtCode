/***************************************************************************************************
**      2022-03-11  HIconStyle
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtCore/QSize>

class QLabel;
class QAbstractButton;
class QPushButton;
class QToolButton;

HE_BEGIN_NAMESPACE

class HIconFontHelperPrivate;

class HIconFontHelper : public QObject
{
    Q_OBJECT

public:
    explicit HIconFontHelper(QObject *parent = nullptr);
    ~HIconFontHelper() override;

public:
    // 样式颜色结构体
    struct StyleColor
    {
        QString position;           // 位置 left right top bottom
        bool defaultBorder;         // 默认有边框

        quint32 iconPixelSize;      // 图标字体尺寸
        QSize iconImageSize;        // 图标图片尺寸

        quint32 borderWidth;        // 边框宽度
        QString borderColor;        // 边框颜色

        QString normalBackground;   // 正常背景颜色
        QString normalTextColor;    // 正常文字颜色
        QString hoverBackground;    // 悬停背景颜色
        QString hoverTextColor;     // 悬停文字颜色
        QString pressedBackground;  // 按下背景颜色
        QString pressedTextColor;   // 按下文字颜色
        QString checkedBackground;  // 选中背景颜色
        QString checkedTextColor;   // 选中文字颜色

        StyleColor();
        // 设置常规颜色 普通状态+加深状态
        void setColor(const QString &normalBackground, const QString &normalTextColor, const QString &darkBackground, const QString &darkTextColor);
    };

public:
    // 获取图形字体
    QFont getFont();
    // 获取指定图形字体，可以指定文字大小，图片大小，文字对齐
    QPixmap getPixmap(const QColor &color, QChar icon, quint32 fontSize = 12, QSize imageSize = QSize(15, 15), int flags = Qt::AlignCenter);

public:
    // 设置图形字体
    void setFamilie(const QString &);
    // 设置图形字体到标签
    void setIcon(QLabel *label, QChar icon, quint32 size = 12);
    // 设置图形字体到按钮
    void setIcon(QAbstractButton *btn, QChar icon, quint32 size = 12);
    // 设置图形字体到图标
    void setPixmap(QAbstractButton *btn, const QColor &color, QChar icon, quint32 fontSize = 12, QSize imageSize = QSize(15, 15), int flags = Qt::AlignCenter);
    // 指定导航面板样式,带图标和效果切换+悬停颜色+按下颜色+选中颜色
    void setStyle(QWidget *widget, QList<QAbstractButton *> btns, QList<QChar> icons, const StyleColor &styleColor);

protected:
    void init();
    void toggled(bool checked);
    bool eventFilter(QObject *watched, QEvent *event) override;

protected:
    QScopedPointer<HIconFontHelperPrivate> d_ptr;
};

HE_END_NAMESPACE
