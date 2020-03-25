#ifndef ERRORS_H
#define ERRORS_H

#include <functional>
#include <map>

float MSE(std::function<float(float x)>, std::map<float, float>);
float MAE(std::function<float(float x)>, std::map<float, float>);

#endif // ERRORS_H
