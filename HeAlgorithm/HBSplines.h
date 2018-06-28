/***************************************************************************************************
**      2018-06-20  HBSplines GSL平滑基样条（B样条）函数类。
**                  B样条与插值样条区别在于所生成的曲线不需要通过每个数据点。
**                  http://www.gnu.org/software/gsl/doc/html/bspline.html
***************************************************************************************************/

#ifndef HBSPLINES_H
#define HBSPLINES_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HBSplines
{
public:
    HBSplines();

public:
    int test();
};

HE_ALGORITHM_END_NAMESPACE

#endif // HBSPLINES_H
