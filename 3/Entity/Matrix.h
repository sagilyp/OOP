#ifndef OOP_LAB3_MATRIX_H
#define OOP_LAB3_MATRIX_H

#include <iostream>
//#include "Cell.h"
#include <limits>
#include <cassert>
template<typename T>
class Matrix;

template <typename T, bool is_const>
class IteratorS{
private:
    friend Matrix<T>;
    const Matrix<T>* matr;
    friend IteratorS<T, !is_const>;
    typedef std::conditional_t<is_const, const T, T>* ptr_t;
    size_t ci;
    size_t cj;
    ptr_t curr;
    int cnt = 0;
    int need = 2;

public:
    size_t geti(){return ci;}
    size_t getj(){return cj;}
    IteratorS(ptr_t ptr, int nd, const Matrix<T>* matr, size_t i, size_t j) noexcept: curr(ptr), need(nd), matr(matr), ci(i), cj(j){};

    typedef ptrdiff_t difference_type; // iterator_traits
    typedef T value_type;
    typedef std::conditional_t<is_const, const T, T>* pointer;
    typedef std::conditional_t<is_const, const T, T>& reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    IteratorS() noexcept: curr(nullptr){};
    //Iterator(Matrix *matrix):curr(matrix->data) {}

//    template<bool other_const>
//    explicit Iterator(Iterator<T, other_const>&& o) noexcept requires(other_const <= is_const): curr(o.curr){
//        o.curr = nullptr;
//    }
//
//    template<T, bool other_const>
//    Iterator& operator =(Iterator<T, other_const>&& o) noexcept requires(other_const <= is_const){
//        curr = o.curr;
//        o.curr = nullptr;
//        return *this;
//    }

    IteratorS& operator ++() noexcept{
        if(cnt == need){
            curr = curr + matr->getCols() - need;
            cj -= cnt;
            ci += 1;
            cnt = 0;
            return *this;
        }
        ++curr;
        ++cnt;
        ++cj;
        return *this;
    }

    IteratorS operator ++(int) noexcept{
        IteratorS res(*this);
        if(cnt == need){
            curr = curr + matr->getCols() - need;
            cj -= cnt;
            ci += 1;
            cnt = 0;
            return res;
        }
        ++curr;
        ++cnt;
        ++cj;
        return res;
    }

    IteratorS& operator --() noexcept{
        if(cnt == 0){
            curr = curr - matr->getCols() + need;
            --ci;
            cj += need;
            cnt = 2;
            return *this;
        }
        --curr;
        --cnt;
        --cj;
        return *this;
    }

    IteratorS operator -- (int) noexcept{
        IteratorS res(*this);
        if(cnt == 0){
            curr = curr - matr->getCols() + need;
            --ci;
            cj += need;
            cnt = 2;
            return res;
        }
        --curr;
        --cnt;
        --cj;
        return res;
    }

    reference operator *() noexcept{
        return *curr;
    }

    std::add_const_t<reference> operator *() const noexcept{
        return *curr;
    }

    pointer operator -> () const noexcept{
        return curr;
    }


    template<bool other_const>
    bool operator ==(const IteratorS<T,other_const>& o) const noexcept{
        return (curr == o.curr);
    }

    template<bool other_const>
    explicit IteratorS(const IteratorS<T, other_const>& o) noexcept requires(other_const <= is_const): curr(o.curr), cnt(o.cnt),
            matr(o.matr), ci(o.ci), cj(o.cj), need(o.need){}

    template<bool other_const>
    IteratorS& operator = (const IteratorS<T, other_const>& o) noexcept requires(other_const <= is_const){
        curr = o.curr;
        cnt = o.cnt;
        matr = o.matr;
        ci = o.ci;
        cj = o.cj;
        need = o.need;
        return *this;
    }


};


template <typename T, bool is_const>
class Iterator{
private:
    friend Matrix<T>;
    friend Iterator<T, !is_const>;
    typedef std::conditional_t<is_const, const T, T>* ptr_t;
    ptr_t curr;


public:
    Iterator(ptr_t ptr) noexcept{ curr = ptr;};

    typedef ptrdiff_t difference_type; // iterator_traits
    typedef T value_type;
    typedef std::conditional_t<is_const, const T, T>* pointer;
    typedef std::conditional_t<is_const, const T, T>& reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    Iterator() noexcept: curr(nullptr){};
    //Iterator(Matrix *matrix):curr(matrix->data) {}

//    template<bool other_const>
//    explicit Iterator(Iterator<T, other_const>&& o) noexcept requires(other_const <= is_const): curr(o.curr){
//        o.curr = nullptr;
//    }
//
//    template<T, bool other_const>
//    Iterator& operator =(Iterator<T, other_const>&& o) noexcept requires(other_const <= is_const){
//        curr = o.curr;
//        o.curr = nullptr;
//        return *this;
//    }

    Iterator& operator ++() noexcept{
        ++curr;
        return *this;
    }

    Iterator operator ++(int) noexcept{
        Iterator res(*this);
        ++curr;
        return res;
    }

    Iterator& operator --() noexcept{
        --curr;
        return *this;
    }

    Iterator operator -- (int) noexcept{
        Iterator res(*this);
        --curr;
        return res;
    }

    Iterator operator +(size_t n) noexcept{
        Iterator res(*this);
        for (auto i = 0; i < n; i++){
            ++res;
        }
        return res;
    }

    Iterator operator -(size_t n) noexcept{
        Iterator res(*this);
        for (auto i = 0; i < n; i++){
            --res;
        }
        return res;
    }

    reference operator *() noexcept{
        return *curr;
    }

    std::add_const_t<reference> operator *() const noexcept{
        return *curr;
    }

    pointer operator -> () const noexcept{
        return curr;
    }

    // ~Iterator() = default;
    template <bool other_const>
    auto operator <=> (const Iterator<T,other_const>& o){
        return curr <=> o.curr;
    }

    template<bool other_const>
    bool operator ==(const Iterator<T,other_const>& o) const noexcept{
        return (curr == o.curr);
    }

//    template<bool other_const>
//    bool operator !=(const Iterator<T,other_const> &o) const noexcept{
//        return (curr != o.curr);
//    }

    template<bool other_const>
    explicit Iterator(const Iterator<T, other_const>& o) noexcept requires(other_const <= is_const): curr(o.curr){}

    template<bool other_const>
    Iterator& operator = (const Iterator<T, other_const>& o) noexcept requires(other_const <= is_const){
        curr = o.curr;
        return *this;
    }


};

static_assert(std::bidirectional_iterator<Iterator<int,true>>);
static_assert(std::bidirectional_iterator<Iterator<int, false>>);

template<typename T>
class Matrix{
private:
    size_t columns;
    size_t rows;
    T** data;
public:
    typedef T value;
    typedef T& reference;
    typedef const T& const_reference;
    typedef Iterator<T, false> iterator;
    typedef IteratorS<T, false> spec_iterator;
    typedef Iterator<T, true> const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    Matrix() /*noexcept(std::is_nothrow_default_constructible_v<T>)*/: columns(0), rows(0), data(nullptr){}

    Matrix(const size_type& _rows, const size_type& _cols): columns(_cols), rows(_rows){
        if(_cols*_rows == 0){
            Matrix{};
            return;
        }
        data = new T*[_rows];
        data[0] = new T[_cols*_rows];
        for (int i = 1; i < _rows; ++i) {
            data[i] = data[0] + i*_cols;
        }
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                data[i][j] = T();
            }
        }
    }


    Matrix(const Matrix& m)
    /*requires std::copy_constructible<T>*/: Matrix(m.rows, m.columns){
        insert(end(), m.begin(), m.end());
//        data = new T*[rows];
//        for (int i = 0; i < rows; ++i) {
//            data[i] = new T[columns];
//        }
//        for (int i = 0; i < rows; ++i) {
//            for (int j = 0; j < columns; ++j) {
//                data[i][j] = m[i][j];
//            }
//        }
    }

    Matrix(Matrix&& m) /*noexcept(std::is_nothrow_default_constructible_v<T>)*/: Matrix(){
        swap(m);
    }

    ~Matrix(){
        if(data == nullptr)
            return;
        delete[] data[0];
        delete[] data;
    }

    Matrix& operator=(const Matrix& m){
//        if(this == &m)
//            return *this;
//        assign(m.begin(), m.end());
//        return *this;

        Matrix<T> temp(m);
        swap(temp);
//        std::swap(temp.data, data);
//        std::swap(columns, temp.columns);
//        std::swap(rows,temp.rows);
        return *this;
    }

    Matrix& operator =(Matrix&& m) noexcept{
        swap(m);
        return *this;
    }

    Matrix& operator =(std::initializer_list<T> il) /*requires std::move_constructible<T>*/{
        assign(std::move(il));
        return *this;
    }

    bool operator ==(const Matrix& m) const{
        return columns == m.columns and rows == m.rows and std::equal(begin(), end(), m.begin(), m.end());
    }

    Matrix<T> operator -(Matrix& m){
        if(columns != m.columns and rows != m.rows){
            throw std::logic_error("Cann't deduct matrix with differnt size");
        }
        Matrix res(rows, columns);
        for (auto it1 = begin(), it2 = m.begin(), it3 = res.begin(); it1 != end() and it2 != m.end() and it3 != res.end();
             ++it1, ++it2, ++it3) {
            *it3 = *it1 - *it2;
        }
        return res;
    }

    Matrix operator +(Matrix& m) {
        if(columns != m.columns and rows != m.rows){
            throw std::logic_error("Cann't add matrix with differnt size");
        }
        Matrix res(rows, columns);
        for (auto it1 = begin(), it2 = m.begin(), it3 = res.begin(); it1 != end() and it2 != m.end() and it3 != res.end();
             ++it1, ++it2, ++it3) {
            *it3 = *it2 + *it1;
        }
        return res;
    }

    Matrix operator *(const Matrix& m) {
        if(columns != m.rows){
            throw std::logic_error("Cann't times matrix with differnt size");
        }
        Matrix res(rows, m.columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < m.columns; ++j) {
                for (int k = 0; k < columns; ++k) {
                    res[i][j] += (*this)[i][k] * m[k][j];
                }
            }
        }
        return res;
    }

    const T* operator[](size_t i) const{
        return data[i];
    }

    T* operator[](size_t i){
        return data[i];
    }

    T& at(const size_type i, const size_type j){
        if(i >= rows or j >= columns){
            throw std::out_of_range("Out of range");
        }
        return data[i][j];
    }

    const T& at(const size_type i, const size_type j) const{
        if(i >= rows or j >= columns){
            throw std::out_of_range("Out of range");
        }
        return data[i][j];
    }

    [[nodiscard]]size_t getRows()const noexcept{return rows;}
    [[nodiscard]]size_t getCols()const noexcept{return columns;}

    [[nodiscard]]size_type size() const noexcept{
        return rows*columns;
    }

    [[nodiscard]]size_type max_size() const noexcept{
        return std::numeric_limits<size_type>::max();
    }

    [[nodiscard]]bool empty() const noexcept{
        return rows*columns == 0;
    }

    void swap(Matrix& o) noexcept{
        //T** first = data;
        //    T* last = (*(data+rows))+columns;
        //T** o_first = o.data;
        //    T* o_last = (*(o.data+o.rows))+o.columns;
        std::swap(data, o.data);
        //    std::swap(last, o_last);
        std::swap(columns, o.columns);
        std::swap(rows, o.rows);
    }

    spec_iterator sbegin(const int& i, const int& j) noexcept{
        int need = 2;
        size_type ii, jj;
        ii = (i-1 >= 0?i-1:0);
        jj = (j-1 >= 0?j-1:0);
        if(j == 0 or j == columns-1)
            need = 1;
        return spec_iterator(data[ii]+jj, need, this, ii, jj);
    }

    spec_iterator send(const int& i, const int& j) noexcept{
        int need = 2;
        size_type ii, jj;
        ii = (i+1 < rows?i+1:rows-1);
        jj = (j+1 < columns?j+1:columns-1);
        if(j == 0 or j == columns-1)
            need = 1;
        return spec_iterator(data[ii]+jj, need, this, ii, jj);
    }

    iterator begin() noexcept{
        return iterator(data[0]);
    }
    iterator end() noexcept{
        return iterator(data[rows-1]+columns);
    }
    const_iterator begin() const noexcept{
        return const_iterator(data[0]);
    }

    const_iterator end() const noexcept{
        return const_iterator(data[rows-1]+columns);
    }

    const_iterator cbegin() const noexcept{
        return const_iterator(data[0]);
    }

    const_iterator cend() const noexcept{
        return const_iterator(data[rows-1]+columns);
    }

    template <typename ... Args>
    iterator emplace(iterator p, Args && ... args)
    {//requires std::constructible_from<T, Args ...>{
        iterator tmp(p-1);
        *tmp = T{std::forward<Args>(args)...};
        return tmp;
    }

    iterator insert(iterator p, const T& t) /*requires std::copy_constructible<T>*/{
        return emplace(p, t);
    }

    iterator insert(iterator p, const T&& t) /*requires std::move_constructible<T>*/{
        return emplace(p, std::move(t));
    }

    iterator insert(iterator p, size_type n, const T& t)
    /*requires std::copy_constructible<T>*/{
        if(n == 0){
            return iterator{const_cast<T*>(p.curr)};
        }
        iterator cnt = p;
        try{
            for (size_type i = 0; i < n; ++i) {
                if(cnt == begin())
                    break;
                insert(cnt, t);
                --cnt;
            }
        }
        catch(...){
            erase(cnt, p);
            throw;
        }
        return p-1;
    }

    template <std::input_iterator It>
    iterator insert(iterator p, It i, It j) /*requires std::copy_constructible<It>*/{
        if(i == j){
            return iterator(const_cast<T*>(p.curr));
        }
        iterator cnt(p+1);
        auto t1(i);
        while(t1 != j){
            if(cnt == begin()+1)
                break;
            --cnt;
            ++t1;
        }
        iterator start(cnt.curr);
        try{
            for (; i != j; ++i) {
                if(cnt == p+1){
                    break;
                }
                insert(cnt, *i);
                ++cnt;
            }
        }
        catch(...) {
            erase(start, cnt);
            throw;
        }
        return p-1;
    }

    iterator insert(iterator p, std::initializer_list<T> il)
    /*requires std::move_constructible<T>*/{
        return insert(p, std::move_iterator(il.begin()), std::move_iterator(il.end()));
    }

    iterator erase(iterator q) noexcept{
        iterator next(q+1);
        T* del = const_cast<T*>(q.curr);
        *del = T{};
        //   del->~T();
        return next;
    }

    iterator erase(iterator q1, iterator q2) noexcept{
        iterator p1 = iterator(const_cast<T*>(q1.curr));
        while(p1 != q2){
            p1 = erase(p1);
        }
        return iterator(const_cast<T*>(q2.curr));
    }

    void clear() noexcept{
        erase(begin(), end());
    }

    template <std::forward_iterator It>
    void assign(It i, It j) /*requires std::copy_constructible<T>*/{
        if(empty()){
            //insert(end(), i, j);
            return;
        }
//        auto first = cbegin();
//        auto last = --cend();
        erase(begin(), end());
        insert(end(), i, j);
        // erase(first, ++last);
    }

    void assign(std::initializer_list<T> il) /*requires std::copy_constructible<T>*/{
        if(empty()){
            //insert(end(), std::move(il));
            return;
        }
        //auto first = cbegin();
        //auto last = --cend();
        erase(begin(), end());
        insert(end(), std::move(il));
        //erase(first, ++last);
    }


    void assign(size_type n, const T& t)
    /*requires std::copy_constructible<T>*/{
        if(empty()){
            //insert(end(), n, t);
            return;
        }
        //auto first = cbegin();
        //auto last = --cend();
        erase(begin(), end());
        insert(end(), n, t);
        //erase(first, ++last);
    }

    reference front(){
        return *begin();
    }

    const_reference front() const{
        return *begin();
    }

    reference back(){
        return *(--end());
    }

    const_reference back() const{
        return *(--end());
    }

    std::pair<size_type, size_type> find(size_type x, size_type y, const T& t, std::pair<size_type, size_type> trace = {0,0}){
        for (auto it = sbegin(x,y) ; it != send(x,y); ++it) {
                if(*it == t){
                    std::pair<size_type, size_type> res =  std::make_pair(it.ci,it.cj);
                    if(res != trace and res != std::make_pair(x,y)){
                        return res;
                    }
                }
        }
        return std::make_pair(0,0);
    }

    void addRow(size_type pos = 0){
        if(pos >= rows)
            pos = rows;
        Matrix<T> nmatr(rows+1, columns);
        nmatr.insert(nmatr.begin() + columns*pos, begin(), begin() + columns*pos);
        nmatr.insert(nmatr.end(), begin() + columns*pos, end());
        *this = nmatr;
    }

    void addCol(size_type pos = 0){
        if(pos >= columns)
            pos = columns;
        Matrix<T> nmatr(rows, columns+1);
        for (int i = 0; i < rows; ++i) {
            nmatr.insert(nmatr.begin()+ nmatr.columns*i + pos, begin()+ columns*i, begin()+ columns*i + pos);
            nmatr.insert(nmatr.begin()+ nmatr.columns*(i+1), begin() + columns*i + pos, begin()+ columns*(i+1));
        }
        *this = nmatr;
    }


};




//    template <typename ... Args>
//    void emplace_front(Args ... args) requires std::constructible_from<T, Args ...>{
//        emplace(begin(), std::forward<Args>(args)...);
//    }
//
//    template <typename ... Args>
//    void emplace_back(Args ... args) requires std::constructible_from<T, Args ...>{
//        emplace(end(), std::forward<Args>(args)...);
//    }

//    void push_front(const T& t)
//    requires std::copy_constructible<T>
//    {
//        insert(begin(), t);
//    }
//
//    void push_front(T&& t)
//    requires std::move_constructible<T>
//    {
//        insert(begin(), std::move(t));
//    }
//
//    void push_back(const T& t)
//    requires std::copy_constructible<T>
//    {
//        insert(end(), t);
//    }
//
//    void push_back(T&& t)
//    requires std::move_constructible<T>
//    {
//        insert(end(), std::move(t));
//    }
//
//    void pop_front() noexcept {
//        erase(begin());
//    }
//
//    void pop_back() noexcept {
//        erase(--end());
//    }


//    Matrix(size_type n, const T& t) requires std::copy_constructible<T>: Matrix(){
//        insert(end(), n, t);
//    }

//    template <std::input_iterator It>
//    Matrix(It i, It j) requires std::constructible_from<T, std::iter_reference_t<It>>: Matrix(){
//        insert(end(), i, j);
//    }

//    Matrix(std::initializer_list<T> il)
//    requires std::move_constructible<T>: Matrix(){
//        insert(end(), std::move(il));
//    }
#endif //OOP_LAB3_MATRIX_H

