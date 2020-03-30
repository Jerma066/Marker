#ifndef GRAPHOBJECTS_H
#define GRAPHOBJECTS_H

#include <functional>
#include <vector>
#include <math.h>
#include <QString>

class Point{
public:
    Point();
    Point(float x, float y, float x_error, float y_error);
    ~Point() = default;

public:
    float x;
    float y;
    float x_error;
    float y_error;
};

class GraphObjects
{
public:
    GraphObjects(std::vector<float> x_values,
                 std::vector<float> y_values,
                 std::vector<float> x_errors,
                 std::vector<float> y_errors,
                 std::vector<float> coefficients);

    ~GraphObjects();

private:
   std::vector<float> _coefficients;
   std::vector<Point> _points_values;
   std::function<float (float)> _dependance;
   QString _equation_str;
};

//Служебные функции
QString MakeStrEquetion(const std::vector<float>& coeffs);

#endif // GRAPHOBJECTS_H
