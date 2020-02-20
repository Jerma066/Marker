#include "coefficients_functions.h"

std::vector<float> linear_coef_methond(const std::map<float, float>& data)
{
    std::vector<float> answer;

    size_t n = data.size();
    float mean_y = 0;
    float mean_x = 0;
    float mean_xy = 0;
    float mean_x2 = 0;

    for(auto it = data.begin(); it != data.end(); it++){
        mean_y += it->second;
        mean_x += it->first;
        mean_xy += it->first * it->second;
        mean_x2 += it->first * it->first;
    }

    mean_y /= n;
    mean_x /= n;
    mean_xy /= n;
    mean_x2 /= n;

    float a = (mean_xy - (mean_x*mean_y)) / (mean_x2 - (mean_x*mean_x));
    float b = mean_y - (a * mean_x);

    answer.push_back(a);
    answer.push_back(b);

    return answer;
}
