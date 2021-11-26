#include "HTestAlgorithm.h"
#include "HeAlgorithm/HRegister.h"
#include "HeAlgorithm/HChromaticity.h"
#include "HeAlgorithm/HIesTm30.h"
#include "HeAlgorithm/HCie.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtDebug>

HE_ALGORITHM_USE_NAMESPACE

void HTestAlgorithm::testRegister()
{
    HRegister reg;
    if (reg.check())
        return;

    // 注册
    auto id = reg.registerId();
    auto code = reg.encrypt(id);
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

void HTestAlgorithm::testIesTm30()
{
    int i;
    double x, y;
    QPolygonF spdt;

    QFile file("testdata.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    for (i = 0; i < 401; i++)
    {
        in >> x >> y;
        spdt << QPointF(x, y);
    }
    file.close();

    HCieDaylight day;
    HIesTm30 ies;

    auto spdr = day.calcRefSourceSpectrum(2937.7, QPointF(380, 780), 1); // 2938
    auto resu = ies.calc(spdr, spdt);
    qDebug() << resu.dEi;
    qDebug() << resu.Rfi;
    qDebug() << resu.dE;
    qDebug() << resu.Rf;
    qDebug() << resu.Rg;
    qDebug() << resu.hj.Rcs;
    qDebug() << resu.hj.Rhs;

}
