
#ifndef OOP_LAB3_GETNUMBER_H
#define OOP_LAB3_GETNUMBER_H

#include <limits>
#include <iostream>
#include <cstring>

template <typename T>
T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()){
    T a;
    while(true){
        std::cin >> a;
        if(std::cin.eof()){
            throw std::runtime_error("Failed to read number: EOF(end of file)");
        }
        else if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong! Please repeat input again: " << std::endl;
        }
        else if(std::cin.bad()){
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        }
        else if(a >= min and a <= max){
            return a;
        }
    }
}

#endif //OOP_LAB3_GETNUMBER_H
