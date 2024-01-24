//
// Created by Gareev Rustam on 04.09.2023.
//

#ifndef OOP1_MATRIX_H
#define OOP1_MATRIX_H

#include <iostream>
#include <limits>
#include <string>
#include <cstring>


namespace mtr{
    template <typename T>
    class Vector {
    private:  
    	int sz = 0;
        int cap = 0;
        T *arr = nullptr;
    public:
        Vector() = default;
        Vector(size_t cap){
            this->cap = cap;
            arr = new T[cap];
        }
        ~Vector(){
            delete[] arr;
        }
        Vector(Vector& v){
            v.sz = sz;
            v.cap = cap;
            v.arr = new T[cap];
            for(int i = 0; i < cap; ++i){
                //v.arr[i] = new(arr+i) T(arr[i]);
                v.arr[i] = arr[i];
            }
        }

        Vector& operator = (const Vector& v){
            sz = v.sz;
            cap = v.cap;
            arr = new T[cap]();
            for(int i = 0; i < sz; ++i)
                arr[i] = v.arr[i];
            return *this;
        }

        void push_back(const T& x){
            if(sz < cap){
                arr[sz] = x;
                ++sz;
                return;
            }
            T* newarr = new T[cap*2];
            for(int i = 0; i < cap; ++i){
               // newarr[i] = new(newarr+i) T(arr[i]);
               newarr[i] = arr[i];
            }
            newarr[cap] = x;
            ++sz;
            delete[] arr;
            arr = newarr;
            cap != 0? cap <<= 1: cap = 1;
        }
        const T& operator [](size_t i)const{
            return arr[i];
        }
        T& operator [](size_t i){
            return arr[i];
        }
        T& at(size_t i){
            if(i >= cap){
                throw std::out_of_range("Out of range");
            }
            return arr[i];
        }
        const T& at(size_t i)const{
            if(i >= cap){
                throw std::out_of_range("Out of range");
            }
            return arr[i];
        }
        size_t size() const{
            return sz;
        }
        size_t capacity(){
            return cap;
        }
    };

    template <typename T>
    void swap(T& x, T& y){
        T t = x;
        x = y;
        y = t;
    }

    srtuct Matrix{
		int rows = 0;
		int columns = 0;
        Vector<int> index = 1;
        Vector<double> data = 1;
        Vector<int> indptr = 1;
    };


    template <typename T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()){
        T a;
        while(true){
            std::cin >> a;
            if(std::cin.eof()){
                throw std::runtime_error("Failed to read number: EOF(end of file)");
            }
            else if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong! Please repeat input again: " << std::endl;
            }
            else if(std::cin.bad()){
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            }
            else if(a >= min and a <= max){
                return a;
            }
        }
    }

    //void erase(Matrix&);
    void input(mtr:: Matrix&);
    void minmax(mtr::Matrix&);
    void output(const char*, const mtr::Matrix&);

}

#endif //OOP1_MATRIX_H
