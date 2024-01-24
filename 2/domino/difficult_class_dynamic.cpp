
#include <ostream>
#include <cstring>
#include <compare>
#include "simple_class.h"
#include "difficult_class_dynamic.h"

using namespace Simp;

namespace DifD{

	/*!
    @param void
    Destroys the "Game" object
	*/
    Game::~Game(){
        std::cout << "Delete\n";
        delete[] arr;
        arr = nullptr;
    }

    /*!
    @param g const Game& value to copy
    @returns Modified "this" object
    Copy constructor
    */
    Game::Game(const Game& g){
        sz = g.sz;
        cap = g.cap;
        delete[] arr;
        arr = new Domino[g.cap];
        for(int i = 0; i < (int)g.cap; ++i){
            arr[i] = g[i];
        }
    }

        /*!
        @param g const Game& value for assignment
        @returns Modified object "this"
        Assignment constructor
        */    
    Game& Game::operator =(const Game& g){
        sz = g.sz;
        cap = g.cap;
        delete[] arr;
        arr = new Domino[cap];
        for(int i = 0; i < (int)g.cap; ++i){
            arr[i] = g[i];
        }
        return *this;
    }

	/*!
	@param cnt size_t the number of "Domino" in the "Game"
	@returns New object
	Creates a new object with "cnt" allocated memory for "Domino"
	*/
	Game::Game(size_t cnt){
	        sz = 0;
	        cap = cnt;
	        arr = new Domino[cnt];
	    }

	/*!
	@param g Game&& reference to rvalue
	@returns Modified object "this"
	Moving constructor
	*/    
	Game::Game(Game&& g) noexcept: arr(g.arr), cap(g.cap), sz(g.sz){ //перемещающий конструктор
	       // std::cout << "Boris Guboslon\n";
	        g.sz = 0;
	        g.cap = 0;
	        g.arr = nullptr;
	    }

	/*!
	@param g Game&& reference to rvalue
	@returns Modified object "this"
	Moving assignment
	*/    
	    Game& Game::operator =(Game&& g) noexcept{ // перемещающее присваивание
	      //  std::cout << "Boris Guboslon\n";
	        delete[] arr;  
	        sz = g.sz;
	        cap = g.cap;
	        arr = g.arr;
	        g.sz = 0;
	        g.cap = 0;
	        g.arr = nullptr;
	        return *this;
	    }

	    /*!
        @param void
        @returns Source object with increased top and bot of each domino by 1 (6+1 = 0)
        Increases fields of each "Domino" by 1
        */
	    Game& Game::operator +(){ // увеличение каждой кости на 1, если переполнение- сброс
	        for(size_t i = 0; i < sz; ++i){
	            Domino& d = arr[i];
	            size_t k = d.getTop();
	            k = (k+1)%7;
	            d.setTop(k);
	            k = d.getBot();
	            k = (k+1)%7;
	            d.setBot(k); // вернуть новый экзепл
	        }
	        return *this;
	    }

    /*!
    @param void
    @returns Source object with reduceded top and bot of each domino by 1 (0-1 = 0)
    Reduces fields of each "Domino" by 1
    */
	    Game& Game::operator -(){ //уменьшение каждой кости на 1, если 0-1 - 0
	        for(size_t i = 0; i < sz; ++i){
	            Domino& d = arr[i];
	            size_t k = d.getTop();
	            k == 0? k = 0: --k;
	            d.setTop(k);
	            k = d.getBot();
	            k == 0? k = 0: --k;
	            d.setBot(k);
	        }
	        return *this;
	    }

    /*!
     @param void
     @returns Source object with inverted top and bot of each domino
     Turns each domino over
    */
	    Game& Game::operator !(){ // все кости переворачиваются
	        for(size_t i = 0; i < sz; ++i){
	            ~arr[i];
	        }
	        return *this;
	    }

    /*!
    @param os stream for output
    @param g const Game& the object to be output
    @returns Output stream
    Outputing "Game" to the stream
    */
	    std::ostream& operator <<(std::ostream& os, const Game& g){
	        for(size_t i = 0; i < g.sz; ++i){
	            Simp::Domino temp = g.arr[i];
	            os << '(' << temp.getTop() <<';' << temp.getBot() << ')' << ',';
	        }
	        os << "\n";
	        return os;
	    }

        /*!
        @param is stream for input
        @param g Game& the object where the stream is written
        @returns Input stream
        Entering "Game" from the stream
        */
	    std::istream& operator >>(std::istream& is, Game& g) { // ввод из потока
	        size_t cnt;
	        Domino d;
	        Game gg;
	       	g.~Game();
	        is >> cnt;
	        for(size_t i = 0; i < cnt; ++i){
	            is >> d;
	            gg.push_back(d);
	        }
	        g = std::move(gg);
	        return is;
	    }

        /*!
            @param gg const Game& the first term
            @param g const Game& the second term
            @returns New object(result of addition)
            Adding two "Game"
        */
	    Game operator +(const Game& gg, const Game& g){
	        Game res(gg.sz+g.sz);
	        res.sz = res.cap;
	        std::copy(gg.arr, gg.arr+gg.sz, res.arr);
	        std::copy(g.arr, g.arr+g.sz, res.arr+gg.sz);
	        return  res;
	    }

    /*!
    @param g const Game& decreasing value
    @param gg const Game& subtracted value
    @returns New object(result of subtraction)
        @throw runtime_error if first operand should is less than second operand
    Subtracting two "Game"
    */
	    Game operator -(const Game& g, const Game& gg){ // вычитание колод, размер первого операнда должен быть >= второго
	        if(g.sz < gg.sz)
	            throw std::runtime_error("first operand should be bigger then second operand");
	        Game res = g;
	        for(size_t i = 0; i < gg.sz; ++i){
	            res[i] = res[i] - gg[i];
	        }
	        return res;
	    }

     /*!
        @param g const Game& the first multiplier
        @param gg const Game& the second multiplier
        @returns New object(the result of multiplication)
        @throw runtime_error if first operand's size isn't equal to second operand's size
        Multiplication two "Game"
    */
	    Game operator *(const Game& g, const Game& gg){ // умножение по модулю 7, оба операнда одинакового размера
	        if(g.sz != gg.sz)
	            throw std::runtime_error("first operand's size should be equal to second operand's size");
	        Game res(g.sz);
	        res.sz = g.sz;
	        for(size_t i = 0; i < res.sz; ++i){
	            res.arr[i] = g.arr[i]*gg.arr[i];
	        }
	        return res;
	    }

    /*!
    @param g const Game& the term
    @returns Modified this object(result of addition)
    @throw runtime_error if summary size is larger then static value of capacity(cap)
    Addition with assignment the "Game"
    */
	    Game& Game::operator +=(const Game& g){
	        *this = *this + g;
	        return *this;
	    }

   /*!
        @param g const Game& the divisible
        @param gg const Game& the divider
        @returns New object(the result of division)
        @throw logic_error when dividing by zero
        @throw runtime_error if first operand's size is non equal to second operand's size"
        division two "Game"
    */
	    Game operator /(const Game& g, const Game& gg){ // деление по модулю 7, оба операнда одинакового размера
	        if(g.sz != gg.sz)
	            throw std::runtime_error("first operand's size should be equal to second operand's size");
	        Game res(g.sz);
	        res.sz = g.sz;
	        for(size_t i = 0; i < res.sz; ++i){
	            res.arr[i] = g.arr[i]/gg.arr[i];
	        }
	        return res;
	    }

        /*!
        @param g const Game& subtracted value
        @returns Modified this object(result of subtraction)
        @throw runtime_error if first operand should is less than second operand
        Subtracting with assignment the "Game"
        */
	    Game& Game::operator -=(const Game& g){
	        *this = *this - g;
	        return *this;
	    }

        /*!
        @param g const Game& multiplier
        @returns Modified this object(result of multiplication)
        @throw runtime_error if first operand's size isn't equal to second operand's size
        Multiplication with assignment the "Game"
        */
	    Game& Game::operator *=(const Game& g){
	        *this = *this * g;
	        return *this;
	    }

        /*!
        @param g const Game& the divider
        @returns Modified this object(result of division)
        @throw logic_error when dividing by zero
        @throw runtime_error if first operand's size is non equal to second operand's size"
        Division with assignment the "Game"
        */
	    Game& Game::operator /=(const Game& g){
	        *this = *this + g;
	        return *this;
	    }

    /*!
    @param void
    @returns The value of summation
    Summing top and bot of every domino in "Game"
    */
	    size_t Game::sum() const{
	        size_t res = 0;
	        for(size_t i = 0; i < sz; ++i){
	            res += arr[i].getBot() + arr[i].getTop();
	        }
	        return res;
	    }

     /*!
    @param g const Game& the object being compared
    @returns Logical type(true or false)
    Comparison of two objects
    */
	    bool Game::operator <(const Game& g) const{
	        if(sz != g.sz)
	            throw std::runtime_error("first operand's size should be equal to second operand's size");
	        if(this->sum() < g.sum())
	            return true;
	        return false;
	    }

     /*!
        @param g const Game& the object being compared
        @returns Logical type(true or false)
        Equivalence check
    */
	    bool Game::operator ==(const Game& g) const{
	        if(sz != g.sz)
	            throw std::runtime_error("first operand's size should be equal to second operand's size");
	        for(size_t i = 0; i < sz; ++i){
	            if(!(arr[i] == g.arr[i]))
	                return false;
	        }
	        return true;
	    }

     /*!
    @param d const Domino& the object being compared
    @returns Logical type(true or false)
    Comparison of two objects
    */
	    bool Game::operator >(const Game& g) const{
	        if(g < *this and !(g == *this))
	            return true;
	        return false;
	    }

    /*!
    @param g const Game& the object being compared
    @returns The value of the order of two objects
    Comparison of two objects
    */
	    std::strong_ordering Game::operator <=>(const Game &g) const{ //great, less
	        if(g == *this)
	            return std::strong_ordering::equal;
	        if(g < *this)
	            return std::strong_ordering::less;
	        return  std::strong_ordering::greater;
	    }
	
    /*!
    @param domino const Domino& inserted object
    Inserting a "Domino" object at the end
    */
    void Game::push_back(const Domino& domino){
        if(sz < cap) {
            arr[sz] = domino;
            sz++;
            return;
        }
        cap == 0? cap = 1:cap = cap;
        Domino* newarr = new Domino[cap*2];
        for(int i = 0; i < static_cast<int>(sz); ++i){
            newarr[i] = arr[i];
        }
        newarr[sz] = domino;
        ++sz;
        delete[] arr;
        arr = newarr;
        cap <<= 1;
    }

        /*!
        @param void
        @returns The value of allocated memory in the array
        Getter of "cap"
        */
    size_t Game::capacity() const{
        return cap;
    }

        /*!
        @param void
        @returns The value of occupied memory in the array
        Getter of "sz"
        */
    size_t Game::size() const{
        return sz;
    }

   /*!
    @param ptr size_t pointer to a place in the array
    @returns Reference to "Domino" object
        @throw out_of_range if array is full
    Accessing the memory area
    */
    Domino& Game::at(size_t ptr){
        if(ptr >= cap){
            throw std::out_of_range("Out of range");
        }
        return arr[ptr];
    }

    /*!
    @param ptr size_t pointer to a place in the array
    @returns Reference to "Domino" object
    @throw out_of_range if array is full
    Accessing the memory area(for constant objects)
    */
    const Domino& Game::at(size_t ptr) const{
        if(ptr >= cap){
            throw std::out_of_range("Out of range");
        }
        return arr[ptr];
    }

    /*!
    @param ptr size_t pointer to a place in the array
    @returns Reference to "Domino" object
    Accessing the memory area
    */
    Domino& Game::operator [](size_t ptr){
        return arr[ptr];
    }

    /*!
    @param ptr size_t pointer to a place in the array
    @returns Reference to "Domino" object
    Accessing the memory area(for constant objects)
    */
    const Domino& Game::operator [](size_t ptr) const{
        return arr[ptr];
    }

    /*!
    @param ptr int pointer to a place in the array
    @returns Modified this object(result of shifting)
    Shifts part of the array to the left starting from "ptr"
    */
    Game& Game::shift_l(int ptr){
        if(ptr < 0 or arr == nullptr){
            return *this;
        }
        for(int i = ptr; i < static_cast<int>(sz-1); ++i){
            arr[i] = arr[i+1];
        }
        --sz;
        return *this;
    }

    /*!
        @param cnt size_t the number of dominoes in the "Game" or the number of different sets of dominoes in the "Game"
        @param t bool true(random) or false(all kinds of)
        @returns New object "Game"
        Create a "Game" object with random dominoes(true) or all kinds of dominoes(false)
    */
    Game::Game(size_t cnt, bool t){ //рандом(true) или всевозможные(false)
        if(t){
            arr = new Domino [cnt];
            cap = cnt;
            sz = cnt;
            for(int i = 0; i < static_cast<int>(cnt); ++i) {
                Domino tmp = Domino::rnd();
                arr[i] = tmp;
            }
            return;
        }
        arr = new Domino [cnt*28];
        sz = 28*cnt;
        cap = 28*cnt;
        size_t ptr = 0;
        for(int i = 0; i < 7; ++i){
            for(int j = i; j < 7; ++j){
                for(int k = 0; k < static_cast<int>(cnt) and ptr < sz; ++k and ++ptr){
                    Domino tmp(i,j);
                    arr[ptr] = tmp;
                }
            }
        }
    }

    /*!
    @param domino const Domino& the term
    @returns Modified this object(result of addition)
    @throw out_of_range if array is full
    Addition definite domino to the "Game"
    */
    Game& Game::operator +=(const Domino& domino){ //добавление заданной кости
        this->push_back(domino);
        return *this;
    }

    /*!
    @param void
    @returns Modified this object(result of addition)
    @throw out_of_range if array is full
    Addition random domino to the "Game"(prefix entry)
    */
    Game& Game::operator ++(){ //добавление случайной кости
        Domino tmp = Domino::rnd();
        this->push_back(tmp);
        return *this;
    }

    /*!
        @param int plug
        @returns Copy of this object before addition
        @throw out_of_range if array is full
        Addition random domino to the "Game"(postfix entry)
    */
    Game Game::operator ++(int){ //добавление случайной кости(постфиксная запись), должна вернуться копия изначального объекта
        Game g(*this);
        ++(*this);
        return g;
    }

    /*!
    @param void
    @returns Modified this object(withdrawal result)
    Taking a random domino from the "Game"
    */    
    Domino Game::operator ~(){ //изъятие случайной кости
        int ptr = static_cast<int>(std::rand() % sz);
        Domino res = arr[ptr];
        this->shift_l(ptr);
        return res;
    }

    /*!
    @param top size_t value of upper part of "Domino"
    @param bot size_t value of lower part of "Domino"
    @returns Modified this object(withdrawal result)
    @throw invalid_argument if there are illegal argument top or bot
    @throw logic_error if there are no definite member of "Game"
    Taking a definite domino from the "Game"
    */
    Domino Game::definite(size_t top, size_t bot){ //изьятие заданной кости
        if((int)top > 6 or (int)top < 0 or (int)bot > 6 or (int)bot < 0)
            throw std::invalid_argument("illegal argument top or bot");
        int ptr = 0;
        for(int i = 0; i < static_cast<int>(sz); ptr = ++i){
            if(arr[i].getTop() == top and arr[i].getBot() == bot){
                break;
            }
        }
        if(ptr == sz)
            throw std::logic_error("No definite member of GAME");
        Domino res = arr[ptr];
        this->shift_l(ptr);
        return res;
    }

    /*!
    @param ptr size_t pointer to a place in the array
    @returns Modified this object(deleting result)
    @throw invalid_argument if there are illegal argument ptr
    Deletes a definite domino from the "Game" by pointer
    */    
    Game& Game::del(size_t ptr){ // удаление кости по номеру
        if(ptr > sz or ptr < 1)
            throw std::invalid_argument("illegal argument ptr");
        this->shift_l(static_cast<int>(ptr-1));
        return *this;
    }

    /*!
    @param void
    @returns Modified this object(result of sorting)
    Sorts "Game" the domino points in ascending order
    */
    Game& Game::sorting(){ //упорядочивание по возрастанию суммы очков
        std::qsort(
            arr, sz, sizeof(Domino),
            [](const void* x, const void* y){
                const Domino arg1 = *static_cast<const Domino*>(x);
                const Domino arg2 = *static_cast<const Domino*>(y);
                const auto cmp = (arg1 <=> arg2);
                if (cmp < 0)
                    return -1;
                if (cmp > 0)
                    return 1;
                return 0;
            }
                );
        return *this;
    }

    /*!
    @param value size_t the value of upper or lower part in "Domino" that is being searched for
    @returns Modified this object(result of finding)
    Finds the first "Domino" suitable for the conditions and removes it from the "Game"
    */
    Game Game::find(size_t value){
        Game res;
        if(arr == nullptr or sz < 1)
            return res;
        for(int i = 0; i < (int)sz; ++i){
            if(arr[i].getTop() == value or arr[i].getBot() == value){
                res.push_back(arr[i]);
                this->shift_l(i);
                --i;
            }
        }
        return res;
    }

    /*!
    @param c stream for output
    @param msg string the message to printing
    @returns Output stream
    Outputing "Game" to the stream with definite message
    */    
    std::ostream& Game::print(std::ostream &c, std::string msg) const {
        c << msg;
        for(int i = 0; i < (int)sz; ++i){
            Simp::Domino temp = arr[i];
            c << '(' << temp.getTop() <<';' << temp.getBot() << ')' << ',';
        }
        c << "\n";
        return c;
    }
}

