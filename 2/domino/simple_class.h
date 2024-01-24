
#ifndef OOP2_EASY_CLASS_H
#define OOP2_EASY_CLASS_H

#include <iostream>
#include <compare>
#include <random>
#include <ostream>
#include <limits>
#include <cstring>

namespace Simp{
    template<typename T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof()) {
                throw std::runtime_error("Failed to read number: EOF(end of file)");
            } else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong! Please repeat input again: " << std::endl;
            } else if (std::cin.bad()) {
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            } else if (a >= min and a <= max) {
                return a;
            }
        }
    }

/*!
        * \author GRR
        * \version 2.3
        * \date 1949-2023
        * \copyright MEPHI-Moscow
*/
    class Domino {
    private:
        size_t top = 0;
        size_t bottom = 0;
    public:
        static int cnt;

        Domino();
        static Domino rnd();
        Domino(size_t top, size_t bottom);
        ~Domino();
        Domino(const Domino &d);
        Domino &operator=(const Domino &d);
        Domino &random();
        Domino &operator~();
        bool operator==(const Domino &d) const;
        bool operator > (const Domino &d) const;
        bool operator < (const Domino &d) const;
        std::strong_ordering operator<=>(const Domino &d) const;
        friend std::istream& operator >>(std::istream&, Domino&);
        friend Domino operator -(const Domino&, const Domino&);
        friend Domino operator +(const Domino&, const Domino&);
        friend Domino operator *(const Domino&, const Domino&);
        friend Domino operator /(const Domino&, const Domino&);        

        std::ostream &art(std::ostream &c) const;
        size_t getTop() const;
        size_t getBot() const;
        void setTop(const size_t top);
        void setBot(const size_t bot);
    };

    Domino new_d();
}
#endif //OOP2_EASY_CLASS_H
