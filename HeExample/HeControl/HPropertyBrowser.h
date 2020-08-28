/***************************************************************************************************
**      2020-07-13  HPropertyBrowser 属性浏览器
**                  参考qtpropertybrowser
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

class QtProperty;

HE_CONTROL_BEGIN_NAMESPACE

class HPropertyBrowserPrivate;

class HPropertyBrowser : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool showParent  READ isShowParent   WRITE setShowParent)

public:
    explicit HPropertyBrowser(QWidget *parent = nullptr);
    ~HPropertyBrowser() override;

public:
    QObject *object() const;
    bool isShowParent() const;
    void setObject(QObject *);
    void setShowParent(bool b);

protected:
    HPropertyBrowser(HPropertyBrowserPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HPropertyBrowserPrivate> d_ptr;

private:
    void init();
    void clear();
    void build();
    void handleValueChanged(QtProperty *, const QVariant &);
};

HE_CONTROL_END_NAMESPACE
