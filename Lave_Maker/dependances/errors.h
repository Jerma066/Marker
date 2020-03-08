#ifndef ERRORS_H
#define ERRORS_H

#include <functional>
#include <QMap>
#include <cmath>

float MSE(std::function<float(float x)>, QMap<float, float>);
float MAE(std::function<float(float x)>, QMap<float, float>);

#endif // ERRORS_H
