/***************************************************************************************************
**      2022-11-09  HColorThemeStyle
***************************************************************************************************/

#pragma once

#include "IStyle.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HColorThemeStylePrivate;

class HColorThemeStyle : public QObject, public IStyle
{
    Q_OBJECT

public:
    explicit HColorThemeStyle(QObject *parent = nullptr);
    ~HColorThemeStyle() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;
    QString toStyleSheet(QVariantMap param = QVariantMap()) override;

public:
    void setStyle(QWidget *obj,
                  int topRadius = 5,                                // 圆角半径上
                  int bottomRadius = 5,                             // 圆角半径下
                  int topBorderWidth = 1,                           // 边框宽度上
                  int rightBorderWidth = 1,                         // 边框宽度右
                  int bottomBorderWidth = 1,                        // 边框宽度下
                  int leftBorderWidth = 1,                          // 边框宽度左
                  const QString &borderColor = "#000000",           // 边框颜色
                  const QString &backgroundColor = "#1ABC9C");      // 背景颜色

protected:
    HColorThemeStyle(HColorThemeStylePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HColorThemeStylePrivate> d_ptr;
};

HE_END_NAMESPACE

