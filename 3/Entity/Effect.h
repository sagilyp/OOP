
#ifndef OOP_LAB3_EFFECT_H
#define OOP_LAB3_EFFECT_H

#include <iostream>

class Enemy;

	/**
     * Перечисление типов эффекта
    */
    enum EffectType{ POISONING, WEAKING, SLOWING }; //отравление, ослабление, замедление

    class Effect {
    private:
        size_t actionTime;
        size_t valuePer;
        EffectType type;
        size_t qnt;
    public:
    	/**
    	     * @brief Конструктор.
    	     * Инициализирует объект заданными значениями
    	     * @param t тип эффекта
    	     * @param a время действия
    	     * @param b величина действия
    	     * @param d нанесенный башней урон
    	*/
        Effect(EffectType t = POISONING, size_t a = 0, size_t b = 0, size_t d = 0): actionTime(a), valuePer(b), type(t), qnt(d) {}
        /**
             * @brief Конструктор копирования.
             * Создает новый объект, копируя значения из другого объекта того же типа.
             * @param other Ссылка на объект для копирования.
        */
        Effect(const Effect& other) = default;
        /**
             * @brief Деструктор.
             * уничтожает объект
        */
        ~Effect() = default;

		/**
		     * @brief Геттер текущего времени действия
		     * @return время действия эффекта
		*/
        size_t getActionTime() const{ return actionTime;}
        /**
             * @brief Геттер величины эффекта
             * @return величина эффекта
        */
        size_t getValuePer() const { return valuePer;}
        /**
             * @brief Сеттер времени действия эффекта
             * @param tm значение времени действия
        */
        void setActionTime(size_t tm){actionTime = tm;}
        /**
             * @brief Сеттер величины эффекта
             * @param val значение величины эффекта
        */
        void setValuePer(size_t val){valuePer = val;}
        /**
             * @brief Геттер типа эффекта
             * @return тип эффекта
        */
        EffectType getType(){return type;}
        /**
             * @brief Сеттер типа эффекта
             * @param tp тип эффекта
        */
        void setType(EffectType tp){type = tp;}

		/**
		     * @brief Нанесение урона врагу
		     * Применяет данный эффект на враге
		     * @param enm ссылка на врага
		*/
        bool damage(Enemy &enm);
    };


#endif //OOP_LAB3_EFFECT_H

