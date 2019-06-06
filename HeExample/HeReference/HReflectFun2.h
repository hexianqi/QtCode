/***************************************************************************************************
**      2018-06-19  HReflectFun2 反射函数范例（不使用槽技术）。
***************************************************************************************************/

#ifndef HREFLECTFUN2_H
#define HREFLECTFUN2_H

#include "HReferenceGlobal.h"
#include <QtCore/QObject>
#include <QtCore/QVariant>

HE_REFERENCE_BEGIN_NAMESPACE

class HReflectFun2 : public QObject
{
    Q_OBJECT

public:
    explicit HReflectFun2(QObject *parent = nullptr);

public:
    QVariantMap process(const QVariantMap &request);

private:
    // request:
    //   "cmd"   : "set_config"
    //   "key"   : keyname
    //   "value" : QVariant
    // reply:
    //   "error" : error message
    QVariantMap process_set_config(const QVariantMap &);
    // request:
    //   "cmd"   : "get_config"
    //   "key"   : keyname
    // reply:
    //   "error" : error message
    //   "value" : QVariant
    QVariantMap process_get_config(const QVariantMap &);
    // request:
    //   "cmd"   : "get_json"
    // reply:
    //   "error" : error message
    //   "json"  : utf8 json
    QVariantMap process_get_json(const QVariantMap &);

private:
    // "key1" : QVariant
    // "key2" : QVariant
    // ...
    QVariantMap _settings;
};

HE_REFERENCE_END_NAMESPACE

#endif // HREFLECTFUN2_H
