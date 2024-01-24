
#ifndef LAB3_UI_H
#define LAB3_UI_H

#include <iostream>
class Game;
class Landscape;

class UI{
private:
    //std::ostream& variants;
public:

	/**
	     * @brief Отрисовка уровня
	     * Рисует карту, текущее расположение врагов и конструкций на карте
	     * @param out поток для вывода
	     * @param land ссылка на уровень для отрисовки
	     * @return модифицированный поток для вывода
	*/
    std::ostream& draw(std::ostream& out, Landscape& land);
    /**
         * @brief Взаимодействие с пользователем
         * Общается с пользователем и выполняет его команды
         * @param gm Ссылка на объект игры для взаимодействия
    */
    void choose(Game& gm);

};

#endif //LAB3_UI_H

