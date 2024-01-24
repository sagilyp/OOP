#ifndef OOP_LAB3_CELL_H
#define OOP_LAB3_CELL_H

class Construction;
#include <iostream>

enum LandType{ FOREST, FIELD, ROAD, LAIR, CASTLE };

class Cell{
private:
    Construction* ptrCnstr;
    LandType type;
public:
	/*!
	     * @brief Конструктор по умолчанию
	     *@returns новый объект класса
	     */
    Cell() noexcept: ptrCnstr(nullptr), type(FIELD){}
    /*!
         * @brief Конструктор
         * @param lt тип местности
         * @param cnstrPtr указатель на конструкцию
         * @returns новый объект класса
         */
    Cell(LandType lt, Construction* cnstrPtr = nullptr) noexcept: type(lt), ptrCnstr(cnstrPtr){};
    /*!
         * @brief Конструктор копирования
         * @param cl  копируемый объект
         * @returns новый объект класса
       */
    Cell(const Cell& cl) noexcept{
        ptrCnstr = cl.ptrCnstr;
        type = cl.type;
    }
    /*!
       * @brief Копирующий оператор присваивания
       * @param cl копируемый объект
       * @returns измененный объект класса
    */
    Cell& operator = (const Cell& cl){
        Cell tmp(const_cast<Cell&>(cl));
        std::swap(tmp, *this);
        return *this;
    }
    /*!
       * @brief Копирующий оператор присваивания
       * @param type тип местности
       * @returns измененный объект класса
    */
    Cell& operator = (const int& type){
        Cell tmp(static_cast<LandType>(type));
        std::swap(tmp, *this);
        return *this;
    }
    /*!
     	* @brief Перемещающий конструктор копирования
     	* Создает новый объект, перемещая значения из другого объекта того же типа
     	* @param cl R-value ссылка на объект для перемещения
        * @returns новый объект класса
    */
    Cell(Cell&& cl) noexcept{
        type = cl.type;
        ptrCnstr = cl.ptrCnstr;
        cl.ptrCnstr = nullptr;
    }
     /**
     * @brief Перемещающий оператор присваивания.
     * Перемещает значения из другого объекта того же типа в текущий объект.
     * @param other R-value ссылка на объект для перемещения.
     * @return Ссылка на текущий объект после перемещения.
     */
    Cell& operator = (Cell&& cl) noexcept{
        type = cl.type;
        ptrCnstr = cl.ptrCnstr;
        cl.ptrCnstr = nullptr;
    }
        /**
     * @brief Деструктор
     * Уничтожает объект
     */
    ~Cell() noexcept = default;

    /**
     * @brief Геттер типа клетки
     * @return Тип клетки
     */
    LandType& getType() { return type;}
        /**
     * @brief Сеттер типа клетки
     * Устанавливае тип местности клетки
     * @param lt тип клетки
     */
    void setType(const LandType& lt){ type = lt;}
        /**
     * @brief Геттер конструкции, расположенной в клетке
     * @return Указатель на конструкцию
     */
    Construction* getCnstr(){ return (ptrCnstr);}
        /**
     * @brief Сеттер для конструкции
     * Устанавливает конструкцию в клетку
     * @param pC указатель на конструкцию
     */
    void setCnstr(Construction* pC){ ptrCnstr = pC; }
        /**
     * @brief Оператор эквивалентности
     * Сравнивает две клетки
     * @param cl ссылка на объект для сравнения.
     * @return true, если указатели на конструкции совпадают и тип местности совпадает, и false иначе
     */
    bool operator == (const Cell& cl){
        return ptrCnstr == cl.ptrCnstr and type == cl.type;
    }
};


#endif //OOP_LAB3_CELL_H

