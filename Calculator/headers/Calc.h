#pragma once
#include <iostream>
#include <vector>
#include <stdexcept> 
using namespace std;
class Calc {
public:
    double multiply(const std::vector<double>& operands);
    double divide(const std::vector<double>& operands);
};
