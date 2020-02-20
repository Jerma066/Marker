#include "errors.h"

//MSE
float MSE(std::function<float (float)> dependance, std::map<float, float> values)
{
    float error = 0;
    size_t n = values.size();

    //pair->first = x; pair->second = y
    for(auto pair = values.begin(); pair != values.end(); pair++){
        error += pow((dependance(pair->first) - pair->second), 2);
    }
    
    return error/n;
}

//MAE
float MAE(std::function<float (float)> dependance, std::map<float, float> values)
{
    float error = 0;
    size_t n = values.size();

    //pair->first = x; pair->second = y
    for(auto pair = values.begin(); pair != values.end(); pair++){
        error += abs((dependance(pair->first) - pair->second));
    }
    
    return error/n;
}
