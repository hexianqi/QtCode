/***************************************************************************************************
**      2021-11-17  HIesTm30            IES TM-30-18数据计算类。
**                  CIE1964             CIE1964数据。
**                  IES_CES             IES_CES数据。
**                  CIE_CAM02           CIE_CAM02数据。
**                  CAM02_UCS           CAM02_UCS数据。
**                  IES_TM30            IES_TM30数据。
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include <QtGui/QPolygonF>
#include <memory>

HE_ALGORITHM_BEGIN_NAMESPACE

struct CIE_CAM02;
struct IES_TM30;

// CMF(color matching function) = 10
struct CIE1964
{
    double wave;
    double X;
    double Y;
    double Z;
};

struct IES_CES
{
    double wave;
    double CES[100];
};

struct CAM02_UCS
{
public:
    CAM02_UCS();

public:
    void calc(CIE_CAM02 *cam, QList<QVector<double>> XYZ);

public:
    QVector<double> h;
    QVector<double> Jp;     // J'
    QVector<double> ap;     // a'
    QVector<double> bp;     // b'
};

struct IES_HUE_BIN
{
public:
    IES_HUE_BIN();

public:
    void calc(IES_TM30 *, double factor);
    QMap<int, QList<int> > group(QVector<double>);

public:
    QVector<double> hbincenters;

public:
    QVector<double> at;
    QVector<double> bt;
    QVector<double> ar;
    QVector<double> br;
    QVector<double> atn;
    QVector<double> btn;
    QVector<double> arn;
    QVector<double> brn;
    QVector<double> dE;
    QVector<double> Rf;
    QVector<double> Rcs;
    QVector<double> Rhs;
    double Rg;
};

struct IES_TM30
{
public:
    IES_TM30();

public:
    void calc(double factor);

public:
    CAM02_UCS test;         // Test
    CAM02_UCS refe;         // Reference
    IES_HUE_BIN hj;         // Hue bin
    QVector<double> dEi;    // ΔEi
    QVector<double> Rfi;    // Rfi
    double dE;              // ΔE
    double Rf;              // Rf
    double Rg;              // Rg
};

class Q_DECL_EXPORT HIesTm30
{
public:
    HIesTm30();

public:
    IES_TM30 calc(const QPolygonF &spdt, const QPolygonF &spdr);

protected:
    void readCie();
    void readCes();
    QList<QVector<double>> calcTristimulus(const QPolygonF &spd);

protected:
    double _factor;
    std::shared_ptr<CIE_CAM02> _cieCam02;
    QVector<CIE1964> _cie1964;
    QVector<IES_CES> _iesCes;
};

HE_ALGORITHM_END_NAMESPACE

