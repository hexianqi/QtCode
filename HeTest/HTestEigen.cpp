#include "HTestEigen.h"
#include "Eigen/Core"
#include <QtCore/QMetaType>
#include <QtCore/QDebug>
#include <iostream>

using namespace Eigen;

Q_DECLARE_METATYPE(Eigen::MatrixXd)
Q_DECLARE_METATYPE(Eigen::ArrayXXd)

QDebug operator<<(QDebug dbg, const MatrixXd &m)
{
    std::cout << m << std::endl << std::endl;
    return dbg.maybeSpace();
}

void HTestEigen::test1()
{
    MatrixXd m1 = MatrixXd::Random(4, 6);
    ArrayXXd a1 = ArrayXXd::Random(6, 10);

    MatrixXd m3 = a1.matrix();
    ArrayXXd a3 = m1.array();

    auto v1 = QVariant::fromValue(m1);
    auto m2 = v1.value<MatrixXd>();
    auto v2 = QVariant::fromValue(a1);
    auto a2 = v2.value<ArrayXXd>();
    auto b1 = m1 == m2;
    auto v3 = QVariant::fromValue(m3);
    qDebug() << v1;
    qDebug() << v2;
    qDebug() << b1;
    qDebug() << m2;
    qDebug() << a1;
    qDebug() << a2;
    qDebug() << m3;
    qDebug() << a3;
}
