#include "HTestAlgorithm.h"
#include "HeAlgorithm/HRegister.h"
#include "HeAlgorithm/HChromaticity.h"
#include <QtCore/QDebug>

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

void HTestAlgorithm::testChromaticity()
{
    HChromaticity cie;
    cie.exportCieUcs("2300", QPointF(2300, 5000), 2);
    cie.exportCieUcs("5000", QPointF(5000, 10000), 5);
    cie.exportCieUcs("10000", QPointF(10000, 15000), 10);
    cie.exportCieUcs("15000", QPointF(15000, 20000), 20);
    cie.exportCieUcs("20000", QPointF(20000, 25000), 50);
}
