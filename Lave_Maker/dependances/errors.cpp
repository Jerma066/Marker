#include "errors.h"

//MSE
float MSE(std::function<float (float)> dependance, QMap<float, float> values)
{
    float error = 0;
    int n = values.size();

    //pair.key() = x; pair.value() = y
    for(auto pair = values.begin(); pair != values.end(); pair++){
        error += pow((dependance(pair.key()) - pair.value()), 2);
    }
    
    return error/n;
}

//MAE
float MAE(std::function<float (float)> dependance, QMap<float, float> values)
{
    float error = 0;
    int n = values.size();

    //pair.key() = x; pair.value() = y
    for(auto pair = values.begin(); pair != values.end(); pair++){
        error += abs((dependance(pair.key()) - pair.value()));
    }
    
    return error/n;
}
