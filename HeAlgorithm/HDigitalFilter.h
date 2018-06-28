/***************************************************************************************************
**      2018-06-20  HDigitalFilter GSL数字滤波函数类。
**                  http://www.gnu.org/software/gsl/doc/html/filter.html
**                  BUG: 头文件"gsl/gsl_movstat.h"中gsl_movstat_accum结构包含delete与关键字冲突。
***************************************************************************************************/

#ifndef HDIGITALFILTER_H
#define HDIGITALFILTER_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

enum HFilterEndType
{
  PadZero,  // 零填充
  PadValue, // 第一个和最后一个值填充
  Truncate  // 不执行填充
};

class HE_ALGORITHM_EXPORT HDigitalFilter
{
//public:
//    //高斯滤波
//    static QVector<double> gaussian(HFilterEndType type, int k, double alpha, int order, QVector<double> x);
//    static QVector<double> gaussianKernel(int k, double alpha, int order, int normalize);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HDIGITALFILTER_H
