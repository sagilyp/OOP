
#ifndef OOP_LAB3_GAME_H
#define OOP_LAB3_GAME_H

#include <iostream>
#include "../json/single_include/nlohmann/json.hpp"
#include <fstream>

class Enemy;
class Landscape;

using json = nlohmann::json;

class Game{
private:
    size_t level;
    size_t time;
    json levels;
    json upgrade;
    json landscape;
    json save;
public:
    Landscape* land;

	/**
	     * @brief Конструктор по умолчанию.
	     * Инициализирует объект по умолчанию
	*/
    Game();
    /**
         * @brief Конструктор копирования.
         * Создает новый объект, копируя значения из другого объекта того же типа.
         * @param other Ссылка на объект для копирования.
    */
    Game(const Game& other) = default;
    /**
         * @brief Деструктор
         * Уничтожает объект
    */
    ~Game() = default;

	/**
	     * @brief Геттер для объекта json
	*/
    const json& getLevels() const {return levels;}
    /**
         * @brief Геттер для объкта json
    */
    const json& getUpgrade() const {return upgrade;}
    /**
         * @brief Геттер для объекта json
    */
    const json& getLandscape() const {return landscape;}
    /**
         * @brief Геттер для текущего времени игры
    */
    size_t getTime() const{ return time;}
    /**
         * @brief Сеттер для текущего времени игры.
    */
    void setTime(size_t t){time = t;}
    /**
         * @brief Геттер для текущего уровня игры
     */
    size_t getLevel() const{ return level;}

	/**
	     * @brief Улучшение башни 
	     * Улучшает башню в соответствии с координатами
	     * @param x, y Координаты башни.
	*/
    void towerUpd(const size_t& x, const size_t& y);
    /**
         * @brief Улучшение замка
    */
    void castleUpd();
    /**
         * @brief Конструктор копирования.
         * Строит башню в поле
         * @param x,y координаты для постройки
         * @param t_type тип башни
         * @paran e_type тип эффекта
    */
    void build(const size_t& x, const size_t& y, int t_type, int e_type);
    /**
         * @brief Разрушение башни
         * Уничтожает башню по координатам
         * @param x,y координаты постройки
    */
    void raze(const size_t& x, const size_t& y);
    /**
         * @brief Делает ход для все игры
         * Ходят враги, стреляют башни, выходят новые враги и умирают погибшие враги
    */
    void makeMove();
    /**
         * @brief Загрузка информации
         * Загружает информацию из конфигурационных файлов
    */
    void uploadInformation();
    /**
         * @brief Очистка игры
         * Удвляются конструкции и враги, освобождается память.
    */
    void erase();
  //  void saveGame();
};

#endif //OOP_LAB3_GAME_H

