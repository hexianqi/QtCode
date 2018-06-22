#include "HTestAlgorithm.h"
#include "HeAlgorithm/HRegister.h"
#include <QDebug>

HE_ALGORITHM_USE_NAMESPACE

void HTestAlgorithm::testRegister()
{
    HRegister reg;
    if (reg.checkRegisterCode())
        return;

    auto id = reg.getRegisterId();
    auto code = reg.encrypt(id);
    qDebug() << id;
    qDebug() << code;
    reg.setRegisterCode(code);
}
