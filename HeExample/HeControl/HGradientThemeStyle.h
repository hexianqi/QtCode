/***************************************************************************************************
**      2022-11-09  HGradientThemeStyle
***************************************************************************************************/

#pragma once

#include "IStyle.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HGradientThemeStylePrivate;

class HGradientThemeStyle : public QObject, public IStyle
{
    Q_OBJECT

public:
    explicit HGradientThemeStyle(QObject *parent = nullptr);
    ~HGradientThemeStyle() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;
    QString toStyleSheet(QVariantMap param = QVariantMap()) override;

public:
    void setStyle(QWidget *obj,
                  int topRadius = 5,                                // 圆角半径
                  const QString &borderColor = "#000000",           // 边框颜色
                  const QString &backgroundStartColor = "#1ABC9C",  // 背景开始颜色
                  const QString &backgroundEndColor = "#FFFFFF");   // 背景结束颜色

protected:
    HGradientThemeStyle(HGradientThemeStylePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGradientThemeStylePrivate> d_ptr;
};

HE_END_NAMESPACE

