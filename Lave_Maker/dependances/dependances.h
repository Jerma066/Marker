#ifndef DEPENDANCES_H
#define DEPENDANCES_H

#include <functional>
#include <vector>

#include "errors.h"

class Dependance
{
public:
    Dependance(std::map<float, float>,  std::function<std::vector<float> (std::map<float, float>)>,
               std::function<float( std::function<float(float x)>, std::map<float, float> )>);

private:
    std::map<float, float> _data;
    float _error_v;
    std::vector<float> _coefficients;
    std::function<float(float x)> _dependance;
    std::function<float( std::function<float(float x)>, std::map<float, float> )> _error_func;
};

#endif // DEPENDANCES_H
