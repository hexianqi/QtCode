/***************************************************************************************************
**      2019-04-12  HSpecFittingTest 光谱拟合数据类（测试）。
***************************************************************************************************/

#pragma once

#include "HSpecFitting.h"

HE_BEGIN_NAMESPACE

class HSpecFittingTestPrivate;

class HSpecFittingTest : public HSpecFitting
{
    Q_DECLARE_PRIVATE(HSpecFittingTest)

public:
    explicit HSpecFittingTest();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;
    QVector<uchar> toBinaryData() override;
    bool fromBinaryData(QVector<uchar> data, int &pos) override;

public:
    void clear() override;
    void setFittingPoints(QPolygonF value) override;
    QVector<double> handle(QVector<double> value, bool abovezero = true) override;

protected:
    void init() override;
    double handle(int i, double value, bool abovezero = true);
    double calcRate(int i, double value);
};

HE_END_NAMESPACE
