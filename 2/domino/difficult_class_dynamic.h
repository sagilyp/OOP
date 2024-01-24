
#ifndef OOP2_HARD_CLASS_H
#define OOP2_HARD_CLASS_H

#include <iostream>
#include <compare>
#include "simple_class.h"


namespace DifD{

/*!
        * \author GRR
        * \version 2.3
        * \date 1949-2023
        * \copyright MEPHI-Moscow
*/
    class Game{
    private:
        Simp::Domino* arr = nullptr;
        size_t sz = 0;
        size_t cap = 0;
    public:
        Game() = default;
        explicit Game(size_t);
        ~Game(); // деструктор
        Game(const Game&); //конструктор копирования
        Game& operator =(const Game&); // конструктор присваивания
        Game(Game&&) noexcept; // перемещающий конструктор
        Game& operator =(Game&&) noexcept; //перемещающее присваивание

        void push_back(const Simp::Domino&);
        size_t capacity() const;
        size_t size() const;
        Simp::Domino& at(size_t);
        const Simp::Domino& at(size_t) const;
        Simp::Domino& operator [](size_t);
        const Simp::Domino& operator [](size_t) const;
        Game& operator +(); // увеличение каждой кости на 1, если переполнение- сброс
        Game& operator -(); // уменьшение каждой кости на 1, если 0-1 - 0
        Game& operator !(); // все кости переворачиваются
        friend std::ostream& operator <<(std::ostream&, const Game&); // вывод game в поток
        friend std::istream& operator >>(std::istream&, Game&); // ввод из потока
        friend Game operator +(const Game&, const Game&); // сложение двух колод домино
        friend Game operator -(const Game&, const Game&); // вычитание двух колод домино
        friend Game operator *(const Game&, const Game&); // умножение по модулю 7
        friend Game operator /(const Game&, const Game&); // деление по модулю 7
        Game& operator +=(const Game&);
        Game& operator -=(const Game&);
        Game& operator *=(const Game&);
        Game& operator /=(const Game&);
        bool operator <(const Game&) const;
        bool operator >(const Game&) const;
        bool operator ==(const Game&) const;
        std::strong_ordering operator <=>(const Game&) const;
        size_t sum() const;

        Game& shift_l(int);
        Game(size_t cnt, bool t); // construct рандом или всевозможные кости
        Game& operator +=(const Simp::Domino& d); // добавление заданной кости
        Game& operator ++(); // добавление случайной кости
        Game operator ++(int); // добавление случайной кости(постфиксная запись)
        Simp::Domino operator ~(); // изъятие случайной кости
        Simp::Domino definite(size_t top, size_t bot); // изъятие заданной кости
        Game& del(size_t num);// удаление кости по номеру
        Game& sorting(); // упорядочивание по возрастанию суммы очков
        Game find(size_t);// поиск подгруппы с заданным значением top или bottom
        std::ostream &print(std::ostream &c, std::string msg = "") const; // вывод
    };
}


#endif //OOP2_HARD_CLASS_H
