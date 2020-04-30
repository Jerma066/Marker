#ifndef GRAPHOBJECTS_H
#define GRAPHOBJECTS_H

#include "genereic/commontypes.h"
#include "dependances/dependances.h"

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

class GraphObject
{
public:
    GraphObject();
    GraphObject(const graphhDataFrame&);
    /*
    GraphObject(std::vector<float> x_values,
                 std::vector<float> y_values,
                 std::vector<float> x_errors,
                 std::vector<float> y_errors,
                 std::vector<float> coefficients);
    */
    ~GraphObject(){};

    float getMin_x() const;
    float getMax_x() const;
    QString getEquation_str() const;

public:
    std::function<float (float)> _dependance;
    std::vector<Point> getPoints_values() const;

private:
    std::vector<float> _coefficients;
    std::vector<Point> _points_values;
    float min_x;
    float max_x;
    QString _equation_str;
};

//Служебные функции
QString MakeStrEquetion(const std::vector<float>& coeffs);

#endif // GRAPHOBJECTS_H
