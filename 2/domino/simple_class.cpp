#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
#include "simple_class.h"
#include <ctime>


namespace Simp {

    int Domino::cnt = 0;

    /*!
    @param void
    @returns New object "Domino"
    Static function - create a class object
    */
	Domino Domino::rnd(){ // конструктор рандомной доминошки
		Domino tmp(0,0);
		tmp.random();
		return tmp;
	}

	/*!
	@param void
	@returns New object "Domino"
	Create a class object
	*/
    Domino::Domino() {
        ++cnt;
    }

	/*!
	@param top size_t top value of "Domino"
	@param bot size_t bottom value of "Domino"
	@returns New object "Domino"  
	Create a class object
	*/	
        Domino::Domino(size_t top, size_t bottom) { // конструктор домино с заданными значениями
        	if(top > 6 or bottom > 6 or top < 0 or bottom < 0){
        		throw std::logic_error("Illegal domino\n");
        	}
            this->top = top;
            this->bottom = bottom;
            ++cnt;
        }

	/*!
	@param void
	Destroys the "Domino" object	
	*/
        Domino::~Domino() {
            --cnt;
        };
	/*!
	@param d const Domino& value to copy
	@returns Modified object d
	Copy constructor
	*/
        Domino::Domino(const Domino &d) { //copy
            top = d.top;
            bottom = d.bottom;
        }

	/*!
	@param d const Domino& value for assignment
	@returns Modified object d
	Assignment constructor
	*/
        Domino& Domino::operator=(const Domino &d) {
            top = d.top;
            bottom = d.bottom;
            return *this;
        }

	/*!
	@param void
 	@returns Source object with random fields
 	Make fields random (from 0 to 6)
	*/
        Domino& Domino::random() { //меняет поля на рандомные
            top = static_cast<size_t>(std::rand() % 7);
            bottom = static_cast<size_t>(std::rand() % 7);
            return *this;
        }

	/*!
	@param void
	@returns Source object with inverted fields top and bot
	Turns the domino over
	*/
        Domino& Domino::operator~() {
            std::swap(top, bottom);
            return *this;
        }
	/*!
	@param d const Domino& the object being compared
	@returns Logical type(true or false)
	Equivalence check
	*/
        bool Domino::operator==(const Domino &d) const {
            if ((top == d.top && bottom == d.bottom) || (top == d.bottom && bottom == d.top))
                return true;
            return false;
        }
    /*!
    @param d const Domino& the object being compared
    @returns Logical type(true or false)
    Comparison of two objects 
    */    
        bool Domino::operator >(const Domino& d) const{
            return (top+bottom > d.top + d.bottom);
        }

    /*!
    @param d const Domino& the object being compared
    @returns Logical type(true or false)
    Comparison of two objects
    */    
        bool Domino::operator <(const Domino& d) const{
            return d > *this;
        }

    /*!
    @param d const Domino& the object being compared
    @returns The value of the order of two objects 
	Comparison of two objects
    */   
        std::strong_ordering Domino::operator <=>(const Domino& d) const{
            if(d == *this)
                return std::strong_ordering::equal;
            if(*this < d)
                return std::strong_ordering::less;
            return std::strong_ordering::greater;
        } 


    /*!
    @param is stream for input
    @param d the object where the stream is writte
    @returns Input stream
    Entering "Dominoes" from the stream
    */
std::istream &operator >>(std::istream &is, Domino &d) {
        size_t top, bot;
        is >> top >> bot;
        d.top = top % 7;
        d.bottom = bot % 7;
        return is;
    }

    /*!
    @param d const Domino& decreasing value
    @param dd const Domino& subtracted value
    @returns New object(result of subtraction)
    Subtracting two "Domino"
    */
    Domino operator -(const Domino& d, const Domino& dd){ //вычитание двух доминошек, в минус не уходит - ставит 0
        int top = d.top - dd.top, bot = d.bottom - dd.bottom;
        top < 0? top = 0: top = top;
        bot < 0? bot = 0: bot = bot;
        Domino res(top, bot);
        return res;
    }

	/*!
    @param d const Domino& the first term
    @param dd const Domino& the second term
    @returns New object(result of addition)
    Adding two "Domino"
    */
    Domino operator +(const Domino& d, const Domino& dd){ // сложение двух доминошек, результат в поле не больше 6
        int top = d.top + dd.top, bot = d.bottom + dd.bottom;
        top %= 7;
        bot %= 7;
        Domino res(top, bot);
        return res;
    }

	/*!
	@param d const Domino& the first multiplier
	@param dd const Domino& the second multiplier
	@returns New object(the result of multiplication)
	Multiplication two "Domino"
	*/
    Domino operator *(const Domino& d, const Domino& dd){ // умножение по модулю 7
        Domino res((d.top*dd.top)%7, (d.bottom*dd.bottom)%7);
        return res;
    }

	/*!
	@param d const Domino& the divisible
	@param dd const Domino& the divider
	@returns New object(the result of division)
	@throw logic_error when dividing by zero
	division two "Domino"
	*/
    Domino operator /(const Domino& d, const Domino& dd){ // деление по модулю 7
        if(dd.top == 0 or dd.bottom == 0)
            throw std::logic_error("divide by zero");
        Domino res((d.top/dd.top)%7, (d.bottom/dd.bottom)%7);
        return res;
    }


	/*!
    @param c stream for output
    @returns ASCII-art of "Domino"
    Drawing a "Domino" object
    */
        std::ostream& Domino::art(std::ostream &c) const {
            size_t cn = top;
            for (int k = 0; k < 2; ++k) {
                c << "~~~~~~" << std::endl;
                for (int i = 0; i < 3; ++i) {
                    c << '|';
                    for (int j = 0; j < 2; ++j) {
                        if (cn > 0) {
                            c << "* ";
                            cn--;
                        } else
                            c << "  ";
                    }
                    c << '|' << std::endl;
                }
                cn = bottom;
            }
            c << "~~~~~~" << std::endl;
            return c;
        }

	/*!
	@param void
	@returns The value of the upper part "Domino"
	Getter of "top"
	*/
        size_t Domino::getTop() const {
            return top;
        }

	/*!
	@param void
	@returns The value of the lower part "Domino"
	Getter of "bot"
	*/
        size_t Domino::getBot() const {
            return bottom;
        }

	/*!
	@param top const size_t the value of the upper part "Domino"
	@throw logic_error if top is more than 6 or less than 0
	Setter of "top"
	*/
        void Domino::setTop(const size_t top) {
        	if(top > 6 or top < 0)
        		throw std::logic_error("Illegal domino\n");
            this->top = top;
        }
	/*!
	@param bot const size_t the value of the lower part "Domino"
	@throw logic_error if bot is more than 6 or less than 0
	Setter of "bot"
	*/
        void Domino::setBot(const size_t bot) {
        	if(bot > 6 or bot < 0)
        	    throw std::logic_error("Illegal domino\n");
            this->bottom = bot;
        }


	/*!
	@param void
	@returns New object "Domino"
	Dialog function for creating a new domino
	*/
        Domino new_d() { // диалоговая функция создания новой доминошки
            Simp::Domino d;
            std::cout << "Enter number of upper part >>\n";
            auto t = getNum<size_t>(0, 6);
            std::cout << "Enter number of lower part >>\n";
            auto b = getNum<size_t>(0, 6);
            d.setTop(t);
            d.setBot(b);
        return d;
    }
}
