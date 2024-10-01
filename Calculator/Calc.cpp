#include "Calc.h"

double Calc::multiply(const std::vector<double>& operands) {
   if(operands.empty()) {
        throw std::invalid_argument("Нет операндов для деления.");
        return 1;
    }
    double result = 1.0; 
    for (const auto& operand : operands) {
        result *= operand;
    }
    return result;
}

double Calc::divide(const std::vector<double>& operands) {
    if(operands.empty()) {
        throw std::invalid_argument("Нет операндов для деления.");
        return 1;
    }
    
    double result = operands[0];
    for (size_t i = 1; i < operands.size(); ++i) {
        if (operands[i] == 0) {
            throw std::runtime_error("Эй, ты чего, еще в школе учат, что на нуль нельзя делить");
        }
        result /= operands[i];
    }
    return result;
}
