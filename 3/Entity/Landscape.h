
#ifndef OOP_LAB3_LANDSCAPE_H
#define OOP_LAB3_LANDSCAPE_H

#include <iostream>
#include <map>
#include <utility>

//#include "Enemy.h"
class Cell;

class Castle;
class Construction;
class Enemy;
#include "Matrix.h"
#include "Cell.h"

class Landscape{
    friend class Game;
private:
//    Matrix<Cell> matrField;
    size_t height;
    size_t width;


public:
    Matrix<Cell> matrField;
    Castle* castlePtr = nullptr;
    std::map<Construction*, std::pair<int,int>> cnstrLocation;
    std::map<Enemy*, std::pair<int,int>> enemyLocation;
    //std::map<int,int> map;
public:
	/**
	     * @brief Конструктор по умолчанию.
	     * Создает новый объект, инициализирую поля нулём
	*/
    Landscape():height(0), width(0){};
    /**
         * @brief Конструктор 
         * Создает новый объект, инициализируя поля в соответствии с заданными значениями
         * @param height высота матрицы
         * @param width ширина матрицы
    */
    Landscape(const size_t height,const size_t width);
    /**
         * @brief Конструктор копирования.
         * Создает новый объект, копируя значения из другого объекта того же типа.
         * @param other Ссылка на объект для копирования.
    */
    Landscape(const Landscape& other);
    /**
         * @brief Деструктор.
         * УНичтожает объект
     */
    ~Landscape() = default;


	/**
	     * @brief Установка клетки
	     * Устанавливает данную клетку по координатам в матрицу
	     * @param x, y координаты для установки клетки
	     * @param cell ссылка на клетку
	*/
    void set(size_t x, size_t y, Cell& cell);
    /**
         * @brief Геттер клетки
         * @param x, y координаты клетки в матрице
    */
    Cell& get(size_t x, size_t y);
    /**
         * @brief Сеетер типа местности
         * @param i, j координаты клетки
         * @param lt тип местности
    */
    void setType(size_t i, size_t j, const LandType& lt){ matrField[i][j].setType(lt);}
    /**
         * @brief Геттер типа клетки
         * @param i, j координаты клетки
    */
    LandType& getType(size_t i, size_t j){return matrField[i][j].getType();}
    /**
         * @brief Сеттер высоты карты
         * @param h высота карты
    */
    void setH(size_t h){ height = h;}
    /**
         * @brief Геттер высоты карты
    */
    [[nodiscard]]size_t getH() const {return height;}
    /**
         * @brief Сеттер ширины карты
         * @param w ширина карты
    */
    void setW(size_t w){width = w;}
    /**
         * @brief Геттер ширины карты
    */
    [[nodiscard]]size_t getW() const {return width;}

	/**
	     * @brief Поиск дороги на карте
	     * Ищет в окрестности точки дорогу
	     * @param curr текущее местоположение
	     * @param trace предыдущее местоположение
	     * @return новое местоположение дороги
	*/
    std::pair<int,int> findRoad(const std::pair<int,int>& curr, const std::pair<int, int>& trace);
    /**
         * @brief Расстояние между точками
         * Считает расстояние между точками
         * @param begin начало отрезка
         * @param end конец отрезка
         * @return посчитанное значение расстояния между точками
    */
    double distance(const std::pair<int,int>& begin, const std::pair<int,int>& end) const;
    /**
         * @brief Постройка конструкции
         * Строит объект в соответствии с местоположением
         * @param constr указатель на конструкцию
         * @param location желаемое местоположение конструкции
         * @return true, если удалось построить, false - иначе
    */
    bool build(Construction* constr, std::pair<int,int> location);
    /**
         * @brief Разрушение постройки
         * Разрушает объект в соответствии с местоположением
         * @param location Местоположение конструкции
         * @return true, если удалось разрушить, false - иначе
    */
    bool raze(const std::pair<int,int>& location);
    /**
         * @brief Проверка правильности ландшафта
         * Проверяет, есть ли путь от замка до каждого логова
         * @return true, если уровень правильный, false - иначе
    */
    bool isTrue();

};

#endif //OOP_LAB3_LANDSCAPE_H

