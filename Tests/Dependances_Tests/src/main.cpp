#include <QCoreApplication>

#include "dependances/errors.h"
#include "dependances/coefficients_functions.h"

#include "test_runner.h"

void TestErrorsFunctions(){

}

void TestCoefficientsOfDependances(){
    std::map<float, float> data_set = {{ 0, 1 }, { 1, 2 }, { 4, 5 }};
    std::vector<float> obtained_coef_answer = linear_coef_method(data_set);
    std::vector<float> expected_coef_answer = {1, 1};
    ASSERT_EQUAL(obtained_coef_answer, expected_coef_answer)

    data_set = {{ 0, 0 }, { 1, 1 }, { 4, 4 }};
    obtained_coef_answer = linear_coef_method(data_set);
    expected_coef_answer = {1, 0};
    ASSERT_EQUAL(obtained_coef_answer, expected_coef_answer)
}

void TestErrorsValues(){
    std::map<float, float> data_set = {{ 0, 1 }, { 1, 2 }, { 4, 5 }};
    std::function<float(float x)> dep = [](float x){return x + 1;};
    ASSERT_EQUAL(MSE(dep, data_set), 0)

    data_set = {{ 0, 0 }, { 1, 1 }, { 5, 5 }};
    dep = [](float x){return x;};
    ASSERT_EQUAL(MSE(dep, data_set), 0)
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestRunner tr;
    RUN_TEST(tr, TestCoefficientsOfDependances);
    RUN_TEST(tr, TestErrorsValues);

    return a.exec();
}
