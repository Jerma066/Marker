#ifndef DEPENDANCES_H
#define DEPENDANCES_H


#include <functional>
#include <QMap>

#include "errors.h"

class LinearDependance
{
public:
    LinearDependance(QMap<float, float>,  std::function<QPair<float, float> (QMap<float, float>)>,
                     std::function<float( std::function<float(float x)>, QMap<float, float> )>);

private:
    QMap<float, float> _data;
    float _error_v;
    QPair<float, float> _coefficients;
    std::function<float(float x)> _dependance;
    std::function<float( std::function<float(float x)>, QMap<float, float> )> _error_func;
};

QPair<float, float> ObshefizCoefMethod(QMap<float, float>);

#endif // DEPENDANCES_H
