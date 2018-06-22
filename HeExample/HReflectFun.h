/***************************************************************************************************
**      2018-06-19  HReflectFun 反射函数范例。
***************************************************************************************************/

#ifndef HREFLECTFUN_H
#define HREFLECTFUN_H

#include "HExampleGlobal.h"
#include <QObject>
#include <QVariantMap>

HE_EXAMPLE_BEGIN_NAMESPACE

class HReflectFun : public QObject
{
    Q_OBJECT

public:
    explicit HReflectFun(QObject *parent = nullptr);

public:
    QVariantMap process(const QVariantMap &request);

private slots:
    // request:
    //   "cmd"   : "set_config"
    //   "key"   : keyname
    //   "value" : QVariant
    // reply:
    //   "error" : error message
    QVariantMap process_set_config(const QVariantMap &request);
    // request:
    //   "cmd"   : "get_config"
    //   "key"   : keyname
    // reply:
    //   "error" : error message
    //   "value" : QVariant
    QVariantMap process_get_config(const QVariantMap &request);
    // request:
    //   "cmd"   : "get_json"
    // reply:
    //   "error" : error message
    //   "json"  : utf8 json
    QVariantMap process_get_json(const QVariantMap &request);

private:
    // "key1" : QVariant
    // "key2" : QVariant
    // ...
    QVariantMap _settings;
};

HE_EXAMPLE_END_NAMESPACE

#endif // HREFLECTFUN_H
