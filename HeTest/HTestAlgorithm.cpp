#include "HTestAlgorithm.h"
#include "HeAlgorithm/HRegister.h"
#include <QDebug>

HE_ALGORITHM_USE_NAMESPACE

void HTestAlgorithm::testRegister()
{
    HRegister reg;
    if (reg.checkRegisterCode())
        return;

    // 注册
    auto id = reg.getRegisterId();
    auto code = reg.encrypt(id);
    qDebug() << id;
    qDebug() << code;
    reg.setRegisterCode(code);

    if (!reg.isExpires())
        reg.trial();
}
