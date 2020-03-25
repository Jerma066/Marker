#include "graphobjects.h"

Point::Point(float x, float y, float x_error = 0, float y_error = 0):
    x(x),
    y(y),
    x_error(x_error),
    y_error(y_error)
{
}

GraphObjects::GraphObjects(std::vector<float> x_values, std::vector<float> y_values,
                           std::vector<float> x_errors, std::vector<float> y_errors,
                           std::vector<float> coeffs):
    _coefficients(coeffs)
{
    if(x_values.size() == y_values.size()){
        _points_values.resize(x_values.size());
        x_errors.resize(x_values.size());
        y_errors.resize(x_values.size());

        for(size_t i = 0; i < x_values.size(); i++){
            _points_values[i].x = x_values[i];
            _points_values[i].y = y_values[i];
            _points_values[i].x_error = x_errors[i];
            _points_values[i].y_error = y_errors[i];
        }

        _dependance = [coeffs](float x) {
            float answer = 0;
            for(auto coef = coeffs.begin(); coef != coeffs.end(); coef++){
                int degree = coeffs.end() - coef;
                answer += *coef * static_cast<float>(pow(x, degree));
            }
            return answer;
        };

    }
    else{
        //TODO: обработать поведение при неккореткных полученных данных
    }
}
