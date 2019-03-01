/***************************************************************************************************
**      2019-03-01  HAbstractBuilder 抽象创建者类。
***************************************************************************************************/

#ifndef HABSTRACTBUILDER_H
#define HABSTRACTBUILDER_H

#include "HGuiGlobal.h"
#include <QObject>

HE_GUI_BEGIN_NAMESPACE

class HAbstractBuilderPrivate;
class HMainWindow;

class HE_GUI_EXPORT HAbstractBuilder : public QObject
{
public:
    explicit HAbstractBuilder(QObject *parent = nullptr);
    ~HAbstractBuilder();

public:
    virtual HMainWindow *createMainWindow() = 0;

protected:
    HAbstractBuilder(HAbstractBuilderPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractBuilderPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTBUILDER_H
