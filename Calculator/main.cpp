#include "Calc.h"
#include <sstream>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void print_help() {
    cout << "=============================\n";
    cout << "          Калькулятор        \n";
    cout << "=============================\n";
    cout << "Использование: ./Calc_m [-o <операция>] <числа>\n\n";
    
    cout << "Опции:\n";
    cout << "   -h, --help     - Показать справку\n\n";
    
    cout << "Операции:\n";
    cout << "   m, multiply  - Умножение\n";
    cout << "   d, divide    - Деление\n\n";

    cout << "Примечание:\n";
    cout << "   Для выполнения операций необходимо указать от 3 до 5 чисел.\n";
    cout << "   Пример: ./Calculator -o m 2 3 4\n";
    
    cout << "=============================\n";
}

bool is_number(const string& s) {
    istringstream iss(s);
    double dummy;
    return !(iss >> dummy).fail();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        print_help();
        return 1;
    }

    Calc calculator;
    int opt;
    string operation;

    while ((opt = getopt(argc, argv, "o:hd")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'o':
                operation = string(optarg);
                break;
            default:
                print_help();
                return 1;
        }
    }

    if (operation.empty()) {
        cerr << "Ошибка: не указан тип операции." << endl;
        print_help();
        return 1; 
    }

    if (operation != "m" && operation != "multiply" && operation != "d" && operation != "divide") {
        cerr << "Ошибка: неверный тип операции. Доступны операции: 'm' (multiply), 'd' (divide)." << endl;
        print_help();
        return 1;
    }

    vector<double> operands;

    for (int i = optind; i < argc; ++i) {
        if (is_number(argv[i])) {
            operands.push_back(stod(argv[i]));
        } else {
            cerr << "Ошибка: '" << argv[i] << "' не является числом." << endl;
            return 1;
        }
    }

    if (operands.size() < 3 || operands.size() > 5) {
        cerr << "Ошибка: для работы калькулятора необходимо ввести от 3 до 5 значений." << endl;
        return 1;
    }

    try {
        double result;
        if (operation == "m" || operation == "multiply") {
            result = calculator.multiply(operands);
            cout << "=============================\n";
            cout << "Результат умножения: " << result << "\n";
            cout << "=============================\n";
        } else if (operation == "d" || operation == "divide") {
            result = calculator.divide(operands);
            cout << "=============================\n";
            cout << "Результат деления: " << result << "\n";
            cout << "=============================\n";
        } else {
            throw invalid_argument("Ошибка: не выбрана операция.");
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
