#include "HIesTm30.h"
#include "HMath.h"
#include "HMatrix.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <QtMath>

HE_ALGORITHM_BEGIN_NAMESPACE

// $F43 = 100                                                               LA (cd/m2)      -> LA
// $F44 = 20                                                                Yb (cd/m2)      -> Yb
// $F45 = 1                                                                 Did             -> Did
// $F46 = 1                                                                 F               -> F
// $F47 = 0.69                                                              c               -> c
// $F49 = IF(F45=1,1,IF(F45<1,F45,F46*(1-(1/3.6)*EXP((-F43-42)/92))))       D               -> D
// $G33 = 7.54                                                              cfactor         -> factor
// G133 = 100*SUMPRODUCT($B5:$B99,xyzs!$F2:$F96,'99set'!C$10:C$104)/SUMPRODUCT($B5:$B99,xyzs!$G2:$G96)  X   -> X
// G134 = 100*SUMPRODUCT($B5:$B99,xyzs!$G2:$G96,'99set'!C$10:C$104)/SUMPRODUCT($B5:$B99,xyzs!$G2:$G96)  Y   -> Y
// G135 = 100*SUMPRODUCT($B5:$B99,xyzs!$H2:$H96,'99set'!C$10:C$104)/SUMPRODUCT($B5:$B99,xyzs!$G2:$G96)  Z   -> Z
// G137 = $F12 = 100                                                        Yw              -> Yw
// G140 = 1/(5*$F$43+1)                                                     k               -> k
// G141 = 0.2*G140^4*5*$F$43+0.1*(1-G140^4)^2*(5*$F$43)^(1/3)               FL              -> FL
// G142 = $F44/G137                                                         n               -> n
// G143 = 0.725*(1/F142)^0.2                                                Nbb             -> Nbb
// G144 = 0.725*(1/F142)^0.2                                                Ncb             -> Ncb
// G145 = 1.48+G142^(1/2)                                                   z               -> z

// G146 = MMULT($I$43:$K$45,G133:G135)                                      R               -> R
// G147 = MMULT($I$43:$K$45,G133:G135)                                      G               -> G
// G148 = MMULT($I$43:$K$45,G133:G135)                                      B               -> B
// G149 = MMULT($I$43:$K$45,F136:F138)                                      Rw              -> R[0]
// G150 = MMULT($I$43:$K$45,F136:F138)                                      Gw              -> G[0]
// G151 = MMULT($I$43:$K$45,F136:F138)                                      Bw              -> B[0]
// G152 = ($F49*(G137/G149)+1-$F$49)*G146                                   Rc              -> Rc
// G153 = ($F49*(G137/G150)+1-$F$49)*G147                                   Gc              -> Gc
// G154 = ($F49*(G137/G151)+1-$F$49)*G148                                   Bc              -> Bc
// G158 = MMULT($M43:$O45,G152:G154)                                        Xc              -> Xc
// G159 = MMULT($M43:$O45,G152:G154)                                        Yc              -> Yc
// G160 = MMULT($M43:$O45,G152:G154)                                        Zc              -> Zc
// G164 = MMULT($Q43:$S45,G158:G160)                                        R'              -> Rp
// G165 = MMULT($Q43:$S45,G158:G160)                                        G'              -> Gp
// G166 = MMULT($Q43:$S45,G158:G160)                                        B'              -> Bp
// G170 = ((400*(G141*G164/100)^0.42)/(((G141*G164/100)^0.42)+27.13))+0.1   R'a             -> Rap
// G171 = ((400*(G141*G165/100)^0.42)/(((G141*G165/100)^0.42)+27.13))+0.1   G'a             -> Gap
// G172 = ((400*(G141*G166/100)^0.42)/(((G141*G166/100)^0.42)+27.13))+0.1   B'a             -> Bap
// G176 = G170-12*G171/11+G172/11                                           a               -> a
// G177 = (1/9)*(G170+G171-2*G172)                                          b               -> b
// G178 = (360/(2*PI()))*ATAN2(G176,G177) {具体参考Excel}                   h               -> h
// G184 = ((12500/13)*$F$48*G144)*(COS((G178*PI()/180)+2)+3.8)              e               -> e
// G185 = (2*G170+G171+(1/20)*G172-0.305)*G143                              A               -> A
// G186 = (2*G173+G174+(1/20)*G175-0.305)*G143                              Aw              -> A[0]
// G187 = 100*(G185/G186)^($F$47*G145)                                      J               -> J
// G189 = (G184*(G176^2+G177^2)^0.5)/(G170+G171+(21/20)*G172)               t               -> t
// G191 = (G189^0.9)*((G187/100)^0.5)*((1.64-0.29^G142)^0.73)               C               -> C
// G192 = G191*G141^0.25                                                    M               -> M
// G209 = (1/0.0228)*LN(1+0.0228*G192)                                      Mc              -> Mp
// G21  = (1+100*0.007)*G105/(1+0.007*G105)                                 Jc(Reference)   -> Jp
// G22  = G127*COS(G96*PI()/180)                                            aM(Reference)   -> ap
// G23  = G127*SIN(G96*PI()/180)                                            bM(Reference)   -> bp
// G25  = (1+100*0.007)*G187/(1+0.007*G187)                                 Jc(Test)        -> Jp
// G26  = G209*COS(G178*PI()/180)                                           aM(Test)        -> ap
// G27  = G209*SIN(G178*PI()/180)                                           bM(Test)        -> bp
// G30  = POWER(POWER(G21-G25,2)+POWER(G22-G26,2)+POWER(G23-G27,2),1/2)     dE              -> dE
// G32  = AVERAGE(G30:DA30)                                                 dEavg           -> dEavg
// Rfi  = 10*LN(EXP((100-$G$33*G30)/10)+1)                                  Rf_i            -> Rf
// Rf   = 10*LN(EXP((100-$G$33*G32)/10)+1)                                  Rf              -> Rfavg


// RG = Calculator!DR26

struct CIE_CAM02
{
public:
    CIE_CAM02();

public:
    int Did;
    double Yb;
    double F;
    double Nc;
    double c;
    double LA;
    double D;
    double Yw;
    double k;
    double FL;
    double n;
    double Nbb;
    double Ncb;
    double z;
    gsl_matrix_view MHPE;
    gsl_matrix_view MCAT02;
    gsl_matrix_view MCAT02inv;
};

double toDegrees(double a, double b)
{
    if (qFuzzyIsNull(a) && qFuzzyIsNull(b))
        return 0.0;
    auto degrees = atan2(a, b) * 180 / M_PI;
    return b >= 0 ? degrees : degrees + 360;
}

CIE_CAM02::CIE_CAM02()
{
    Did = 1;
    Yb = 20.0;
    F = 1.0;
    Nc = 1;
    c = 0.69;
    LA = 100.0;
    D = Did > 1 ? F * (1 - exp((LA + 42) / -92.0) / 3.6) : Did;

    Yw = 100.0;
    k = 1.0 / (5 * LA + 1);
    FL = 0.2 * pow(k, 4) * 5 * LA + 0.1 * pow(1 - pow(k, 4), 2) * pow(5 * LA, 1.0 / 3);
    n = Yb / Yw;
    Nbb = Ncb = 0.725 * pow(n, -0.2);
    z = 1.48 + sqrt(n);

    double a[] = { 0.38971, 0.68898, -0.07868,
                  -0.22981, 1.18340,  0.04641,
                   0.00000, 0.00000,  1.00000 };
    double b[] = { 0.7328, 0.4296, -0.1624,
                  -0.7036, 1.6975,  0.0061,
                   0.0030, 0.0136,	0.9834 };
    double c[] = { 0.7328, 0.4296, -0.1624,
                  -0.7036, 1.6975,  0.0061,
                   0.0030, 0.0136,	0.9834 };
    MHPE = gsl_matrix_view_array(a, 3, 3);
    MCAT02 = gsl_matrix_view_array(b, 3, 3);
    MCAT02inv = gsl_matrix_view_array(c, 3, 3);
    HMatrix::inverse(&MCAT02inv.matrix);
}

void CAM02_UCS::calc(CIE_CAM02 *cam, QList<QVector<double>> XYZ)
{
    for (int i = 0; i < 100; i++)
    {
        X[i] = XYZ[0][i];
        Y[i] = XYZ[1][i];
        Z[i] = XYZ[2][i];
        auto RGB  = HMatrix::mul(&cam->MCAT02.matrix, QVector<double>() << X[i] << Y[i] << Z[i]);
        R[i]  = RGB.at(0);
        G[i]  = RGB.at(1);
        B[i]  = RGB.at(2);
        Rc[i] = (cam->D * (cam->Yw / R[0]) + 1 - cam->D) * R[i];
        Gc[i] = (cam->D * (cam->Yw / G[0]) + 1 - cam->D) * G[i];
        Bc[i] = (cam->D * (cam->Yw / B[0]) + 1 - cam->D) * B[i];
        auto XYZc = HMatrix::mul(&cam->MCAT02inv.matrix, QVector<double>() << Rc[i] << Gc[i] << Bc[i]);
        auto RGBp = HMatrix::mul(&cam->MHPE.matrix, XYZc);
        Rp[i]  = RGBp.at(0);
        Gp[i]  = RGBp.at(1);
        Bp[i]  = RGBp.at(2);
        Rap[i] = 0.1 + 400 * pow(cam->FL * Rp[i] / 100, 0.42) / (27.13 + pow(cam->FL * Rp[i] / 100, 0.42));
        Gap[i] = 0.1 + 400 * pow(cam->FL * Gp[i] / 100, 0.42) / (27.13 + pow(cam->FL * Gp[i] / 100, 0.42));
        Bap[i] = 0.1 + 400 * pow(cam->FL * Bp[i] / 100, 0.42) / (27.13 + pow(cam->FL * Bp[i] / 100, 0.42));
        a[i]   = (Rap[i] - Gap[i] * 12 / 11 + Bap[i] / 11);
        b[i]   = (Rap[i] + Gap[i] - Bap[i] * 2) / 9;
        h[i]   = toDegrees(a[i], b[i]);
        e[i]   =  (3.8 + cos(2 + h[i] * M_PI / 180)) / 4;
        t[i]   = 50000 / 13 * cam->Ncb * cam->Nc * e[i] * sqrt(pow(a[i], 2) + pow(b[i], 2)) / (Rap[i] + Gap[i] + Bap[i] * 21 / 20);
        A[i]   = cam->Nbb * (2 * Rap[i] + Gap[i] + 0.05 * Bap[i] -0.305);
        J[i]   = 100 * pow(A[i] / A[0], cam->c * cam->z);
        C[i]   = pow(t[i], 0.9) * sqrt(J[i] / 100) * pow((1.64 - pow(0.29, cam->n)), 0.73);
        M[i]   = C[i] * pow(cam->FL, 0.25);
        Mp[i]  = log(1 + 0.0228 * M[i]) / 0.0228;
        Jp[i]  = (1 + 100 * 0.007) * J[i] / (1 + 0.007 * J[i]);
        ap[i]  = Mp[i] * cos(h[i] * M_PI / 180);
        bp[i]  = Mp[i] * sin(h[i] * M_PI / 180);
    }
}

IES_TM30::IES_TM30()
{
    dEi.resize(99);
    Rfi.resize(99);
}

void IES_TM30::calc(double factor)
{
    for (int i = 1; i < 100; i++)
    {
        dEi[i - 1] = sqrt(pow(refe.Jp[i] - test.Jp[i], 2) + pow(refe.ap[i] - test.ap[i], 2) + pow(refe.bp[i] - test.bp[i], 2));
        Rfi[i - 1] = 10 * log(exp((100 - factor * dEi[i - 1]) / 10.0) + 1);
    }
    dE = HMath::average(dEi);
    Rf = 10 * log(exp((100 - factor * dE) / 10.0) + 1);
}

HIesTm30::HIesTm30()
{
    _factor = 6.73;
    _cieCam02 = std::make_shared<CIE_CAM02>();
    _iesTm30 = std::make_shared<IES_TM30>();
    readCie();
    readCes();
}

void HIesTm30::calc(const QPolygonF &spdr, const QPolygonF &spdt)
{
    _iesTm30->refe.calc(_cieCam02.get(), calcTristimulus(spdr));
    _iesTm30->test.calc(_cieCam02.get(), calcTristimulus(spdt));
    _iesTm30->calc(_factor);
}

void HIesTm30::readCie()
{
    int i,n;
    QString str;

    QFile file(":/dat/CIE1964.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _cie1964.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
        in >> _cie1964[i].wave >> _cie1964[i].X >> _cie1964[i].Y >> _cie1964[i].Z;
    file.close();
}

void HIesTm30::readCes()
{
    int i,j,n;
    QString str;

    QFile file(":/dat/IES_CES.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _iesCes.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
    {
        in >> _iesCes[i].wave;
        for (j = 0; j < 100; j++)
            in >> _iesCes[i].CES[j];
    }
    file.close();
}

QList<QVector<double> > HIesTm30::calcTristimulus(const QPolygonF &spd)
{
    int i,j,k,l;
    double sum;
    QVector<double> X(100);
    QVector<double> Y(100);
    QVector<double> Z(100);

    i = 0;
    j = 0;
    k = 0;
    sum = 0;
    X.fill(0, 100);
    Y.fill(0, 100);
    Z.fill(0, 100);
    while (i < spd.size() && j < _cie1964.size() && k < _iesCes.size())
    {
        if (fabs(spd[i].x() - _cie1964[j].wave) < 1e-6 && fabs(spd[i].x() - _iesCes[k].wave) < 1e-6)
        {
            for (l = 0; l < 100; l++)
            {
                X[l] += spd[i].y() * _cie1964[j].X * _iesCes[k].CES[l];
                Y[l] += spd[i].y() * _cie1964[j].Y * _iesCes[k].CES[l];
                Z[l] += spd[i].y() * _cie1964[j].Z * _iesCes[k].CES[l];
            }
            sum += spd[i].y() * _cie1964[j].Y;
            i++;
            j++;
            k++;
            continue;
        }
        if (spd[i].x() < _cie1964[j].wave || spd[i].x() < _iesCes[k].wave)
        {
            i++;
            continue;
        }
        if (_cie1964[j].wave < spd[i].x() || _cie1964[j].wave < _iesCes[k].wave)
        {
            j++;
            continue;
        }
        k++;
    }
    sum = 100 / sum;
    for (i = 0; i < 100; i++)
    {
        X[i] = X[i] * sum;
        Y[i] = Y[i] * sum;;
        Z[i] = Y[i] * sum;;
    }
    return { X, Y, Z};
}

HE_ALGORITHM_END_NAMESPACE
