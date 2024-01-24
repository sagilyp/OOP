#include <iostream>
#include "matrix.h"

using namespace mtr;

// основная функция
int main() {
     
    try {
        Matrix matrix;
        input(matrix); // ввод матрицы
        std::cout << "ok" << '\n';
        output("******************* Sourced matrix ***********************", matrix); // вывод матрицы
        minmax(matrix); // вычисление требуемого результата
        output("******************* Destination matrix ***********************", matrix);
        std::cout << "end" << '\n';
   	}
    catch(const std::bad_alloc &ba) { // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch(const std::exception &e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
