#include "dependances.h"

// Класс реализующий зависимость
Dependance::Dependance(std::map<float, float> data,
                       std::function<std::vector<float> (const std::map<float, float>&)> coef_meth,
                       std::function<float (std::function<float (float)>, std::map<float, float>)> error_func):
    _data(data),
    _coefficients(coef_meth(_data)),
    _error_func(error_func)
{
    std::vector<float> coefs = _coefficients;

    _dependance = [coefs](float x) {
        float answer = 0;
        for(auto coef = coefs.begin(); coef != coefs.end(); coef++){
            int degree = coefs.end() - coef - 1;
            answer += *coef * pow(x, degree);
        }
        return answer;
    };

    _error_v = _error_func( _dependance, _data);
}


std::map<float, float> Dependance::getData()
{
    return _data;
}

float Dependance::getErrorValue()
{
    return _error_v;
}

std::vector<float> Dependance::getCoeffcients()
{
    return _coefficients;
}

std::function<float (float x)> Dependance::getDependance()
{
    return _dependance;
}

std::function<float (std::function<float (float)>, std::map<float, float>)> Dependance::getErrorFunc()
{
    return _error_func;
};
