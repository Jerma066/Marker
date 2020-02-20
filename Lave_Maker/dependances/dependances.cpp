#include "dependances.h"
#include "coefficients_functions.h"

// Класс реализующий зависимость
Dependance::Dependance(std::map<float, float> data,
                       std::function<std::vector<float> (std::map<float, float>)> coef_meth = linear_coef_methond,
                       std::function<float (std::function<float (float)>, std::map<float, float>)> error_func = MSE):
    _data(data),
    _coefficients(coef_meth(_data)),
    _error_func(error_func)
{
    std::vector<float> coefs = _coefficients;

    _dependance = [coefs](float x) {
        float answer = 0;
        for(auto coef = coefs.begin(); coef != coefs.end(); coef++){
            int degree = coefs.end() - coef;
            answer += *coef * pow(x, degree);
        }
        return answer;
    };

    _error_v = _error_func( _dependance, _data);
};
