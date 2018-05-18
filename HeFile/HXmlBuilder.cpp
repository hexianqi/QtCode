#include "HXmlBuilder.h"
#include "HXmlElement.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HTypeHelper.h"

HE_CORE_USE_NAMESPACE
HE_FILE_BEGIN_NAMESPACE

template<class T>
T *HXmlBuilder::createObject(HXmlElement *xe)
{
    return HTypeHelper::createObject<T>(xe->attribute("className"));
}

template<class T>
T *HXmlBuilder::createObject(HXmlElement *xe, QVariantMap param)
{
    static_assert(std::is_base_of<IInitializeable, T>::value, "T needs to be IInitializeable based.");
    auto t = createObject<T>(xe);
    if (t != nullptr)
    {
        param["xml"] = QVariant::fromValue(xe);
        t.initialize(param);
    }
    return t;
}

HE_FILE_END_NAMESPACE
