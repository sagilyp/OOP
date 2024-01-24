
#ifndef OOP_LAB3_CONSTRUCTION_H
#define OOP_LAB3_CONSTRUCTION_H


#include <string>
#include <map>
#include <queue>
#include <semaphore>

class Game;

class Landscape;
#include "Enemy.h"

    class Construction {
    protected:
        size_t level = 0;
    public:
    	    /**
     * @brief Геттер уровня
     * @return Текущий уровень конструкции
     */
        size_t getLevel(){return level;}
            /**
     * @brief Сеттер уровня
     * Устанавливает уровень конструкции
     * @param lvl значение уровня
     */
        void setLevel(const size_t& lvl){level = lvl;}
            /**
     * @brief Виртуальная функция улучшенния конструкции
     */
        virtual bool improve(const Game&) = 0;
    };

    class Castle : public Construction {
    private:
        std::string name;
        int gold;
        size_t maxStrength;
        size_t curStrength;
    public:
        /**
     * @brief Конструктор по умолчанию
     * Инициализирует  объект с нулевым значением
     */
        Castle():gold(0), maxStrength(0), curStrength(0){};
            /**
     * @brief Конструктор
     * Инициализирует объект заданными значениями
     * @param _name имя замка
     * @param _gold деньги замка
     * @param _health здоровье замка
     */
        Castle(const std::string& _name, const int _gold, const size_t _health): name(_name), gold(_gold), maxStrength(_health), curStrength(_health){};
	/**
     * @brief Конструктор копирования.
     * Создает новый объект, копируя значения из другого объекта того же типа.
     * @param _castle Ссылка на объект для копирования.
     */
             Castle(const Castle& _castle) = default;
    /**
      * @brief Деструктор
      * Уничтожает объект
     */
        ~Castle() = default;

		/**
	     * @brief Геттер текущего здоровья
	     * @return значение текущего здоровья
	    */
        size_t getCurStrength() const {return curStrength;}
		/**
		     * @brief Сеттер текущего здоровья
		     * Устанавливает значение текущего здоровья
		     * @param str значение здоровья
		*/
        void setCurStrength(size_t str){curStrength = str;}
		/**
		     * @brief Геттер максимального здоровья
		     * @return значение максимального здоровья
		*/
        size_t getMaxStrength() const {return maxStrength;}
        /**
             * @brief Сеттер максимального здоровья
             * Устанавливает значение максимального здоровья
             * @param str значение максимального здоровья
        */
        void setMaxStrength(size_t str){maxStrength = str;}
        /**
             * @brief Геттер денег
             * @return значение денег в данный момент
        */
        size_t getGold() const{ return gold; };
        /**
             * @brief Сеттер денег
             * Устанавливает текущее количество денег
             * @param gl количество денег
             */
        void setGold(size_t gl){gold = gl;}

		/**
		     * @brief Пополнение денег замка
		     * Увеличивает количество денег
		     * @param gl сколько надо начислить
		*/
        void fillUp(const size_t& gl);
        /**
             * @brief Улучшение замка
             * Обновляет характеристики замка в соответствии с конфигурационными файлами
             * @param gm ссылка на игру
        */
        bool improve(const Game& gm) override;
        /**
             * @brief Списание денег с замка
             * Уменьшает количество денег
             * @param gl сколько надо списать
        */
        bool writeOfMoney(size_t gl);
        /**
             * @brief Наненсение урона замку
             * уменьшает здоровье и количество золота замка
             * @param gold сколько будет списано денег с замка
             * @param health сколько будет наненсено урона замку
        */
        void damage(size_t gold, size_t health);
    };

    class Tower : public Construction {
        friend Game;
    protected:
        std::map<std::string, int> characteristics;
    public:
    	    /**
     * @brief Конструктор по умолчанию.
     * Инициализирует объект с нулевым значением данных.
     */	
        Tower() = default;
        /**
             * @brief Конструктор копирования.
             * Создает новый объект, копируя значения из другого объекта того же типа.
             * @param other Ссылка на объект для копирования.
        */
        Tower(const Tower& other) = default;
        /**
             * @brief Деструктор.
             * уничтожает объект
        */
        ~Tower() = default;

		/**
		     * @brief Виртуальная функция выстрела башни
		*/
        virtual void hit(Landscape &) = 0;

        virtual void hit_t(Landscape &, std::binary_semaphore&) = 0;

		/**
		     * @brief Сеттер характеристик
		     * Вставляет заданную характеристику в таблицу
		     * @param str ключ
		     * @param val значение
		*/
        void setChar(const std::string& str, int val){ characteristics[str] = val;}
        /**
             * @brief Геттер характеристик
             * Возвращает значение по ключу
             * @param str ключ
        */
        int getChar(const std::string& str){ return characteristics[str];}
    };

    class MagicTower : public Tower {
    public:
    	/**
    	     * @brief Конструктор
    	     * Создает новый объект в соответствии с заданными значениями 
    	     * @param gm ссылка на объект игры для получения информации
    	     * @param type тип эффекта
    	*/
        MagicTower(const Game& gm, const int& type);
        /**
             * @brief Улучшение башни
             * Обновляет таблицу характеристик 
             * @param gm ссылка на объект игры для получения информации
        */
		bool improve(const Game& gm) override;
		/**
		     * @brief Удар башни
		     * Бьёт ближайшего к башне врага
		     * @param land ссылка на объект ландшафта для получения информации
		*/
        void hit(Landscape& land) override;
        
        void hit_t(Landscape&, std::binary_semaphore&) override;
    };

	class SimpleTower : public Tower {
	    public:
	    	/**
	    		* @brief Конструктор
	    		* Создает новый объект в соответствии с заданными значениями
	    		* @param gm ссылка на объект игры для получения информации
	    	*/	
	        SimpleTower(const Game&);
	        /**
	             * @brief Улучшение башни
	             * Обновляет таблицу характеристик
	             * @param gm ссылка на объект игры для получения информации
	        */
	        bool improve(const Game& gm) override;
	        /**
	              * @brief Удар башни
	              * Бьёт ближайшего к башне врага
	              * @param land ссылка на объект ландшафта для получения информации
	        */
	        void hit(Landscape& land) override;

	        void hit_t(Landscape&, std::binary_semaphore&) override;
	};
	
	 class MagicTrap : public Tower {
	   public:
	   		/**
	            * @brief Конструктор
	   		    * Создает новый объект в соответствии с заданными значениями
	   	        * @param gm ссылка на объект игры для получения информации
	   	        * @param type тип эффекта
	   		*/
	        MagicTrap(const Game& gm, const int& type);
	        /**
	             * @brief Улучшение башни
	             * Обновляет таблицу характеристик
	             * @param gm ссылка на объект игры для получения информации
	        */
	        bool improve(const Game& gm) override;
	        /**
	                 * @brief Удар башни
	                 * Бьёт всех в радиусе поражения
	                 * @param land ссылка на объект ландшафта для получения информации
	        */
	        void hit(Landscape& land) override;

	        void hit_t(Landscape&, std::binary_semaphore&) override;
	 };

    class Lair : public Construction {
    private:
        std::queue<Enemy*> enemys;
        size_t timeBtwWaves = 0;
        size_t cnt = 1;
    public:
    	/**
    	     * @brief Конструктор по умолчанию
    	     * Инициализирует объект нулевым значением
    	*/
        Lair() = default;
        /**
             * @brief Конструктор 
             * Создает новый объект
             * @param tm время между волнами врагов
        */
        Lair(size_t tm): timeBtwWaves(tm){};
        /**
             * @brief Конструктор копирования.
             * Создает новый объект, копируя значения из другого объекта того же типа.
             * @param other Ссылка на объект для копирования.
        */
        Lair(const Lair &other) = default;
        /**
             * @brief Деструктор
             * Уничтожает объект
         */
        ~Lair() = default;


		/**
		     * @brief Геттер времени 
		     * @return возвращает время между волнами врагов
		*/
        size_t getTime() const{return timeBtwWaves;}
        /**
             * @brief Сеттер времени
             * Устанавливает время между волнами врагов
             * @param tm значение времени
        */
        void setTime(const size_t & tm){ timeBtwWaves = tm;}
        /**
             * @brief Сеттер количества врагов в одной волне
             * @param cn количество врагов в одной волне
        */
        void setCnt(const size_t & cn){ cnt = cn;}
        /**
             * @brief Проверка логова
             * Проверяет, пустое ли логово
             * @return true, если логово пустое, false - иначе
        */
        bool empty() const{ return enemys.empty();}

		/**
		     * @brief Улчушение логова
		     * Обновляет логово в соответствии с конфигурационными файлами
		     * @param gm cсылка на объект игры
		     * @return true, если удалось улучшить, false - иначе
		*/
        bool improve(const Game& gm) override;
        /**
             * @brief Выпуск врагов из логова
             * @param land ссылка на объект ландшафта для получения и изменения информации
             * @return true, если удалось выпустить врага, false - иначе
        */
        bool releaseEnemy(Landscape& land);
        /**
             * @brief Выпуск врагов из логова в соответствии с временем.
             * @param gm ссылка на объект игры для получения и изменения информации
             * @return true, если удалось выпустить врага, false - иначе
        */
        bool releaseEnemy_t(const Game& gm);
        /**
             * @brief Пополнение очереди врагов
             * Увеличивает очередь врагов заданным указателем
             * @param enm указатель на врага
        */
        void pushEnemy(Enemy* enm);
    };

#endif //OOP_LAB3_CONSTRUCTION_H

