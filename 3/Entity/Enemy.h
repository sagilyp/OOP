
#ifndef OOP_LAB3_ENEMY_H
#define OOP_LAB3_ENEMY_H


#include <vector>

#include "Effect.h"

class Landscape;
class Game;

    enum EnemyType {
        GOBLIN, MAGICIAN, GIANT
    }; // гоблин, маг, гигант

    class Enemy {
    private:
        EnemyType type;
        size_t maxHealth;
        int curHealth;
        size_t gold;
        size_t maxVelocity;
        size_t curVelocity;
        std::vector<Effect> effects;
        std::pair<int,int> trace;

		/**
		     * @brief Сбор мусора(истекших эффектов)
		     * Очищает вектор эффектов
		     * @param effs ссылка на вектор эффектов
		*/
        void garbageCollection(std::vector<Effect>& effs);

    public:
    	/**
         * @brief Конструктор по умолчанию.
         * Создает новый объект, инициализируя его по умолчанию
        */
        Enemy() = default;
        /**
             * @brief Конструктор
             * Создает новый объект, инициализируя его заданными значениями
             * @param t тип врага
             * @param health здоровье
             * @param g золото
             * @param vel скорость передвижения
             * @param sz размер вектора эффектов
             * @param tr след врага - координаты врага, на которых он уже находился
       */
        Enemy(const EnemyType &t, size_t health, size_t g, size_t vel, size_t sz = 0, std::pair<int, int> tr = {0,0}) :
                type(t), maxHealth(health), curHealth(health), gold(g), maxVelocity(vel), curVelocity(vel), trace(tr) { effects.reserve(sz); }
		/**
		     * @brief Конструктор копирования.
		     * Создает новый объект, копируя значения из другого объекта того же типа.
		     * @param other Ссылка на объект для копирования.
		*/
        Enemy(const Enemy & other) = default;
        /**
             * @brief Деструктор.
             * Уничтожает объект
        */
        ~Enemy() = default;

		/**
		     * @brief Геттер типа врага
		*/
        int getType(){return type;}
        /**
             * @brief Сеттер предыдущего местоположения врага
        */
        void setTrace(std::pair<int,int> trc){ trace = trc;}
        /**
             * @brief Геттер предыдущего местоположения врага
        */
        std::pair<int,int> getTrace() const{ return trace;}
        /**
             * @brief Геттер максимального здоровья врага
        */
        size_t getMaxHealth() const { return maxHealth; }
        /**
             * @brief Сеттер максимального здоровья врага
        */
        void setMaxHealth(size_t health) { maxHealth = health; }
        /**
             * @brief Геттер текущего здоровья врага
        */
        int getCurHealth() const { return curHealth; }
        /**
             * @brief Сеттер текущего здоровья
        */
        void setCurHealth(int health) { curHealth = health; }
        /**
             * @brief Геттер текущей скорости
        */
        size_t getCurVel() const { return curVelocity; }
        /**
             * @brief Сеттер текущего здоровья
        */
        void setCurVel(size_t _velocity) { curVelocity = _velocity; }
        /**
             * @brief Геттер максимальной скорости
        */
        size_t getMaxVel() const { return maxVelocity; }
        /**
             * @brief Сеттер максимального здоровья
        */
        void setMaxVel(size_t _velocity) { maxVelocity = _velocity; }
        /**
             * @brief Геттер золота врага
        */
        size_t getGold(){return gold;}
        /**
             * @brief Сеттер золота врага
        */
        void setGold(size_t g){gold = g;}

		/**
		     * @brief Помещение эффекта в вектор эффектов
		     * @param effect Ссылка на объект эффекта
		*/
        void pushEff(const Effect &effect);
        /**
             * @brief Активация эффекта
             * Действует эффектом на врага
             * @param qnt Величина урона, нанеченного врагу
        */
        void effAct(size_t qnt = 0);
        /**
             * @brief Соверешение хода врагом
             * Меняет местоположение врага
             * @param game ссылка на объект игры для получения и изменения информации
        */
        bool move(Game& game);
        /**
             * @brief Убицство врага
             * Начисляет деньги замку
             * @param land ссылка на объект ландшафта
        */
        bool kill(Landscape& land);

    };



#endif //OOP_LAB3_ENEMY_H

