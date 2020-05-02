#include "graphobject.h"
#include <QDebug>

Point::Point():
    x(0),
    y(0),
    x_error(0),
    y_error(0)
{
}

Point::Point(float x, float y, float x_error = 0, float y_error = 0):
    x(x),
    y(y),
    x_error(x_error),
    y_error(y_error)
{
}

GraphObject::GraphObject():
    _dependance([](float x){return x*0;}),
    _equation_str("")
{
    _coefficients.clear();
    _points_values.clear();
}

GraphObject::GraphObject(const graphhDataFrame& graphDF, const ApproximationMethod& a_m,
                         const ErrorFunctions& e_f)
{
    std::function<std::vector<float> (const std::map<float, float>&)> coef_meth;
    std::function<float( std::function<float(float x)>, std::map<float, float> )> error_func;

    switch (a_m){
    case ApproximationMethod::Linnear:
        coef_meth = linear_coef_method;
        break;
    }
    switch (e_f){
    case ErrorFunctions::MSE:
        error_func = MSE;
        break;
    case ErrorFunctions::MAE:
        error_func = MAE;
        break;
    }
    Dependance dep(graphDF.first, coef_meth, error_func);
    _coefficients = dep.getCoeffcients();
    _dependance = dep.getDependance();
    _equation_str = MakeStrEquetion(_coefficients);

    min_x = graphDF.first.begin()->first;
    max_x = graphDF.first.begin()->first;
    for(auto it = graphDF.first.begin(); it != graphDF.first.end(); it++){
        Point ptn(it->first, it->second, graphDF.second.at(it->first).first,
                  graphDF.second.at(it->first).second);
        if(ptn.x < min_x) {min_x = ptn.x;}
        if(ptn.x > max_x) {max_x = ptn.x;}
        _points_values.push_back(ptn);
    }
}

float GraphObject::getMin_x() const
{
    return min_x;
}

float GraphObject::getMax_x() const
{
    return max_x;
}

QString GraphObject::getEquation_str() const
{
    return _equation_str;
}

std::vector<Point> GraphObject::getPoints_values() const
{
    return _points_values;
}

//Служебные функции
QString MakeStrEquetion(const std::vector<float>& coeffs)
{
    QString result = "y = ";
    for(auto coef = coeffs.begin(); coef != coeffs.end(); coef++){
        int degree = coeffs.end() - coef - 1;
        if(degree > 1){
            result += QString::number(*coef) +"X" + "^" + QString::number(degree) + " + " ;
        }
        else if(degree == 1){
            result += QString::number(*coef) +"X + ";
        }
        else{
            result += QString::number(*coef);
        }
    }
    return result;
}
