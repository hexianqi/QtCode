#include <vector>

using namespace std;

class CProtocolSpec;
class CCalibrateSpec;
class CTestSpec;

class CProtocolFacade
{
public:
    CProtocolFacade();
    ~CProtocolFacade();

public:
    bool openProtocol();
    bool closeProtocol();
    bool setIntegralTime(double value);
    bool setSmooth(int times, int range);
    bool getSpectrumSample(vector<int> &value, double &percent, bool fit);
    bool getSpectrumEnergy(vector<double> &value, double &percent);
    double pelsToWave(int value);
    double handleNonlinear(int value);
    bool setStdCurve(vector<double> value);
    bool setCalibrateData(vector<unsigned char> value);
    bool getCalibrateData(vector<unsigned char> &value);

protected:
    CProtocolSpec *_protocol;
    CCalibrateSpec *_calibrate;
    CTestSpec *_test;
};
