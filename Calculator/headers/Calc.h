#pragma once
#include <iostream>
#include <vector>
#include <stdexcept> 
using namespace std;
class Calc {
public:
    double multiply(const vector<double>& operands);
    double divide(const vector<double>& operands);
};
