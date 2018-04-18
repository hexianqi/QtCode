#ifndef HSPECTRUM_H
#define HSPECTRUM_H

#include "HeAlgorithm_global.h"

class QPointF;

namespace He {
namespace Algorithm {
namespace Spectrum {

//色坐标转换
QPointF xy2uv(QPointF xy);
QPointF uv2xy(QPointF uv);
QPointF uv2uvp(QPointF uv);
QPointF uv2cd(QPointF uv);
//普朗克公式。波长单位为nm
double planck(double wave, double tc);
//普朗克公式关于色温导数。波长单位为nm
double planckPrime(double wave, double tc);

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // HSPECTRUM_H
