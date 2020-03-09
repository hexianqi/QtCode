/***************************************************************************************************
**      2020-01-16  HImageHelper 图片帮助类。
***************************************************************************************************/

#ifndef HIMAGEHELPER_H
#define HIMAGEHELPER_H

#include <QtUiPlugin/QDesignerExportWidget>

class QImage;
class QSize;
class QPen;

class QDESIGNER_WIDGET_EXPORT HImageHelper
{
public:
    // 创建十字图片
    static QImage createCrossImage(QSize size, QPen pen);
};

#endif // HIMAGEHELPER_H
