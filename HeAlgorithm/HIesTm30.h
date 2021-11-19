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

struct CIE_CAM02;

struct CAM02_UCS
{
public:
    void calc(CIE_CAM02 *cam, QList<QVector<double>> XYZ);

public:
    double X[100];
    double Y[100];
    double Z[100];
    double R[100];
    double G[100];
    double B[100];
    double Rc[100];
    double Gc[100];
    double Bc[100];
    double Rp[100];
    double Gp[100];
    double Bp[100];
    double Rap[100];     // Ra'
    double Gap[100];     // Ga'
    double Bap[100];     // Ba'
    double a[100];
    double b[100];
    double h[100];
    double e[100];
    double t[100];
    double A[100];
    double J[100];
    double C[100];
    double M[100];
    double Mp[100];      // M'
    double Jp[100];      // J'
    double ap[100];      // a'
    double bp[100];      // b'
};

struct IES_TM30
{
public:
    IES_TM30();

public:
    void calc(double factor);

public:
    CAM02_UCS refe;         // Reference
    CAM02_UCS test;         // Test
    QVector<double> dEi;    // ΔEi
    QVector<double> Rfi;    // Rfi
    double dE;              // ΔE
    double Rf;              // Rf
};

class HIesTm30
{
public:
    HIesTm30();

public:
    void calc(const QPolygonF &spdr, const QPolygonF &spdt);

protected:
    void readCie();
    void readCes();
    QList<QVector<double>> calcTristimulus(const QPolygonF &spd);

protected:
    double _factor;
    std::shared_ptr<CIE_CAM02> _cieCam02;
    std::shared_ptr<IES_TM30> _iesTm30;
    QVector<CIE1964> _cie1964;
    QVector<IES_CES> _iesCes;
};

HE_ALGORITHM_END_NAMESPACE

