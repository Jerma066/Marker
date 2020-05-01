#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <QVariant>

enum class Orientation {
    Vertical,
    Horizontal,
    NONE
};

enum class ApproximationMethod {
    Linnear
};

enum class ErrorFunctions {
    MSE,
    MAE
};

struct Settings{
    Orientation data_orientation;
    ApproximationMethod approximation_method;
    ErrorFunctions error_function;
};

typedef std::vector<std::vector<float>> dataTable;
typedef QPair<std::map<float, float>, std::map<float, QPair<float, float>>> graphhDataFrame;
typedef std::vector<graphhDataFrame> allGraphsData;


#endif // COMMONTYPES_H
