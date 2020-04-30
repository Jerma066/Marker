#ifndef DEPENDANCES_H
#define DEPENDANCES_H

#include <functional>
#include <vector>

#include "errors.h"
#include "coefficients_functions.h"

class Dependance
{
public:
    Dependance(std::map<float, float> data,
               std::function<std::vector<float> (const std::map<float, float>&)> coef_meth = linear_coef_method,
               std::function<float( std::function<float(float x)>, std::map<float, float> )> error_func = MSE);
    ~Dependance(){};

    std::map<float, float> getData();
    float getErrorValue();
    std::vector<float> getCoeffcients();
    std::function<float(float x)> getDependance();
    std::function<float( std::function<float(float x)>, std::map<float, float> )> getErrorFunc();


private:
    std::map<float, float> _data;
    float _error_v;
    std::vector<float> _coefficients;
    std::function<float(float x)> _dependance;
    std::function<float( std::function<float(float x)>, std::map<float, float> )> _error_func;
};

#endif // DEPENDANCES_H
