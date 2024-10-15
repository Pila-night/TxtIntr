#include "Calc.h"

#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <regex>
#include <regex>
using namespace std;

void print_help()
{
    cout << "=============================\n";
    cout << "          Калькулятор        \n";
    cout << "=============================\n";
    cout << "Использование: ./Calculator <-o <операция>> <числа>\n\n";

    cout << "Опции:\n";
    cout << "   -h, --help     - Показать справку\n\n";

    cout << "Операции:\n";
    cout << "   m, multiply  - Умножение\n";
    cout << "   d, divide    - Деление\n\n";

    cout << "Примечание:\n";
    cout << "   Для выполнения операций необходимо указать от 3 до 5 чисел.\n";
    cout << "   Пример: ./Calculator -o m 2 3 4\n\n ";
    cout << "  Калькулятор умеет работать с числами в экспоненциальной форме.\n";
    cout << "   Пример: ./Calculator -o m 1.45e1 -1.22e-5 1\n";
    cout << "   Внимание! После 'e' должна быть обязательно указана степень.\n";
    cout << "=============================\n";
}


bool is_number(const string& s) {
    const regex pattern(R"([-+]?[0-9]*.?[0-9]+([eE][-+]?[0-9]+)?)");
    return regex_match(s, pattern);
}



bool is_option(const string& s)
{
    if(is_number(s)) {
        return false; 
    }
    return s == "-o" || s == "--help" || s == "m" || s == "multiply" || s == "d" || s == "divide";
}

int main(int argc, char* argv[])
{
    if(argc < 3) {
        print_help();
        return 1;
    }

    Calc calculator;
    string operation;
    vector<double> operands;
    bool operation_found = false;
    for(int i = 1; i < argc; ++i) {
        if(string(argv[i]) == "-o" && (i + 1) < argc) {
            operation = argv[++i]; 
            if(operation != "m" && operation != "multiply" && operation != "d" && operation != "divide") {
                cerr << "Ошибка: Неверная операция: '" << operation << "'.\n";
                print_help();
                return 1;
            }
            operation_found = true; 
        } else if(is_option(argv[i])) {
            continue;
        } else if(is_number(argv[i])) {
            if(operation_found) { 
                operands.push_back(stod(argv[i])); 
            } else {
                cerr << "Ошибка: числа должны стоять после опции '-o' и типа операции." << endl;
                return 1;
            }
        } else {
            cerr << "Ошибка: '" << argv[i] << "' является неизвестной опцией." << endl;
            return 1;
        }
    }

    if(operation.empty()) {
        cerr << "Ошибка: Не указана операция." << endl;
        print_help();
        return 1;
    }

    if(operands.size() < 3 || operands.size() > 5) {
        cerr << "Ошибка: для работы калькулятора необходимо ввести от 3 до 5 значений." << endl;
        return 1;
    }

    if(operation == "m" || operation == "multiply") {
        double result = calculator.multiply(operands);
        cout << "=============================\n";
        cout << "Результат умножения: " << result << "\n";
        cout << "=============================\n";
    } else if(operation == "d" || operation == "divide") {
        try {
            double result = calculator.divide(operands);
            cout << "=============================\n";
            cout << "Результат деления: " << result << "\n";
            cout << "=============================\n";
        } catch(const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            return 1;
        }
    } else {
        print_help();
        return 1;
    }

    return 0;
}
