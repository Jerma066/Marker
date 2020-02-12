#include "dependances.h"


// Линейная зависимость
LinearDependance::LinearDependance(QMap<float, float> data,
                                   std::function<QPair<float, float> (QMap<float, float>)> coef_meth = ObshefizCoefMethod,
                                   std::function<float (std::function<float (float)>, QMap<float, float>)> error_func = MSE):
    _data(data),
    _coefficients(coef_meth(_data)),
    _error_func(error_func)
{
    float a = _coefficients.first;
    float b = _coefficients.second;
    _dependance = [a, b](float x) { return (a*x + b);};
    _error_v = _error_func( _dependance, _data);
};

// Реализация функции поиска коэффициентов
//--TODO: переименовать эту функцию
//--написать ее реализацию
QPair<float, float> ObshefizCoefMethod(QMap<float, float> data)
{
    float a = 0;
    float b = 0;

    return qMakePair(a, b);
}
