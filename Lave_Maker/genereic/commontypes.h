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


#endif // COMMONTYPES_H
