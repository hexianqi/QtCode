#pragma once

#include <memory>
#include <vector>
#include <map>

using namespace std;

struct CIE_CAM02;
struct IES_TM30;

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
    void calc(CIE_CAM02 *cam, vector<vector<double>> XYZ);

public:
    vector<double> h;
    vector<double> Jp;     // J'
    vector<double> ap;     // a'
    vector<double> bp;     // b'
};

struct IES_HUE_BIN
{
public:
    IES_HUE_BIN();

public:
    void calc(IES_TM30 *, double factor);
    map<int, vector<int>> group(vector<double>);

public:
    vector<double> hbincenters;

public:
    vector<double> at;
    vector<double> bt;
    vector<double> ar;
    vector<double> br;
    vector<double> atn;
    vector<double> btn;
    vector<double> arn;
    vector<double> brn;
    vector<double> dE;
    vector<double> Rf;
    vector<double> Rcs;
    vector<double> Rhs;
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
    CAM02_UCS reference;    // Reference
    IES_HUE_BIN hj;         // Hue bin
    vector<double> dEi;     // ΔEi
    vector<double> Rfi;     // Rfi
    double dE;              // ΔE
    double Rf;              // Rf
    double Rg;              // Rg
};

class HIesTm30
{
public:
    HIesTm30();
    ~HIesTm30();

public:
    IES_TM30 calc(vector<double> wave, vector<double> spdt, vector<double> spdr);

protected:
    void readCie();
    void readCes();
    vector<vector<double>> calcTristimulus(vector<double> wave, vector<double> spd);

protected:
    double _factor;
    CIE_CAM02 *_cieCam02;
    vector<CIE1964> _cie1964;
    vector<IES_CES> _iesCes;
};

