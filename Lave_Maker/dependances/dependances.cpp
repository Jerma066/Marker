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
    QMapIterator<float, float> i(data);
    int n = data.size();
    float mean_y = 0;
    float mean_x = 0;
    float mean_xy = 0;
    float mean_x2 = 0;

    while(i.hasNext())
    {
        i.next();

        mean_y += i.value();
        mean_x += i.key();
        mean_xy += i.key() * i.value();
        mean_x2 += i.key() * i.key();
    }
    mean_y /= n;
    mean_x /= n;
    mean_xy /= n;
    mean_x2 /= n;

    float a = (mean_xy - (mean_x*mean_y)) / (mean_x2 - (mean_x*mean_x));
    float b = mean_y - (a * mean_x);

    return qMakePair(a, b);
}
