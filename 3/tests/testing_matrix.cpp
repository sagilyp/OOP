#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Entity/Matrix.h"
#include <vector>

TEST_CASE("Matrix"){
    SECTION("constructor, copy constructor and assign"){
        Matrix<int> matrm(0,2);
        Matrix<int> matr(3, 3);
        matr[2][2] = 9;
        matr[1][1] = 6;
        matr[0][0] = 3;
        REQUIRE(matr.size() == 9);
        Matrix<int> mmatr;
        REQUIRE(mmatr.getCols() == 0);
        REQUIRE(mmatr.getRows() == 0);
        Matrix<int> matr2{matr};
        const Matrix<int> matr3 = matr2;
        REQUIRE(matr2 == matr3);
        REQUIRE(matr2.getCols() == 3);
        REQUIRE(matr2.getRows() == 3);
        REQUIRE(matr3.getCols() == 3);
        REQUIRE(matr3.getRows() == 3);
        REQUIRE(matr3[0][0] == 3);
        REQUIRE(matr3[2][2] == 9);
        Matrix<int> matr4(4,4);
        matr4 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        matr2 = matr4;
        REQUIRE(matr2.size() == 16);
        REQUIRE(matr2[1][1] == 6);
    }
    SECTION("move"){
        Matrix<int> matr2(3,3);
        matr2 = {1,2,3,4,5,6,7,8,9,10,11,12};
        Matrix matr(std::move(matr2));
        REQUIRE(matr.size() == 9);
        REQUIRE(matr[1][1] == 5);
        REQUIRE(matr[2][2] == 9);
        Matrix<int> matr3(2,2);
        matr3 = {5,5,5,5};
        Matrix<int> matr4(std::move(matr3));
        REQUIRE(matr4.size() == 4);
        REQUIRE(matr4[0][0] == 5);
        REQUIRE(matr4[1][1] == 5);
        Matrix<int> matr5 = (std::move(matr4));
        REQUIRE(matr5.size() == 4);
        REQUIRE(matr5[0][0] == 5);
        REQUIRE(matr5[1][1] == 5);
    }
    SECTION("operators"){
        Matrix<int> matr1(3,3);
        matr1[0][0] = 3;
        matr1[1][1] = 6;
        matr1[2][2] = 9;
        Matrix<int> matr2(3,3);
        matr2 = {1,2,3,4,5,6,7,8,9};
        Matrix<int> matr3(2,2);
        matr3 = {3,3,3,3};
        Matrix<int> matr4(matr2);
        REQUIRE(matr4 == matr2);
        Matrix<int> res = matr2 - matr4;
        REQUIRE(res.size() == 9);
        REQUIRE(res[0][0] == 0);
        REQUIRE(res[1][1] == 0);
        res = res + matr2;
        REQUIRE(res.size() == 9);
        REQUIRE(res[0][0] == 1);
        REQUIRE(res[1][1] == 5);
        res = matr1*matr2;
        REQUIRE(res.size() == 9);
        REQUIRE(res[0][0] == 3);
        REQUIRE(res[1][1] == 30);
        const Matrix<int> cres(res);
        REQUIRE(cres[0][0] == 3);
        REQUIRE(cres[1][1] == 30);
        REQUIRE(res.at(0, 0) == 3);
        REQUIRE(res.at(1, 1) == 30);
        REQUIRE(cres.at(0, 0) == 3);
        REQUIRE(cres.at(1, 1) == 30);
        REQUIRE_THROWS(cres.at(100,100));
        REQUIRE_THROWS(res.at(100,100));
        REQUIRE_THROWS(matr2-matr3);
        REQUIRE_THROWS(matr2+matr3);
        REQUIRE_THROWS(matr2*matr3);
    }

    SECTION("getters and swap"){
        Matrix<int> matr2(4,3);
        matr2 = {1,2,3,4,5,6,7,8,9};
        REQUIRE(matr2.getRows() == 4);
        REQUIRE(matr2.getCols() == 3);
        REQUIRE(matr2.size() == 12);
        REQUIRE(matr2.max_size() == std::numeric_limits<size_t>::max());
        REQUIRE(matr2.empty() == false);
        Matrix<int> matr;
        REQUIRE(matr.empty() == true);
        matr.swap(matr2);
        REQUIRE(matr2.empty() == true);
        REQUIRE(matr.empty() == false);
    }

    SECTION("iterators"){
        Matrix<int> matr2(3,3);
        matr2 = {1,2,3,4,5,6,7,8,9};
        Matrix<int> cmatr2(3,3);
        cmatr2 = {1,2,3,4,5,6,7,8,9};
        int cnt = 1;
        for (auto it = matr2.begin(); it != matr2.end() ; ++it) {
            REQUIRE(*it == cnt);
            ++cnt;
        }
        cnt = 1;
        for (auto it = cmatr2.begin(); it != cmatr2.end() ; ++it) {
            REQUIRE(*it == cnt);
            ++cnt;
        }
        cnt = 1;
        for (auto it = matr2.cbegin(); it != matr2.cend() ; ++it) {
            REQUIRE(*it == cnt);
            ++cnt;
        }
    }
    SECTION("emplace"){
        Matrix<int> matr2(3,3);
        matr2 = {1,2,3,4,5,6,7,8,9};
        matr2.emplace(matr2.end(), 2023);
        REQUIRE(matr2[2][2] == 2023);
    }
    SECTION("insert"){
        std::vector<int> vec = {3,3,3,3};
        Matrix<int> matr2(3,3);
        matr2 = {1,2,3,4,5,6,7,8,9};
        matr2.insert(matr2.end(), std::move(2023));
        REQUIRE(matr2[2][2] == 2023);
        matr2.insert(matr2.end(), std::move(2024));
        REQUIRE(matr2[2][2] == 2024);
        matr2.insert(matr2.end(), 3, 1000);
        REQUIRE(matr2[2][0] == 1000);
        REQUIRE(matr2[2][1] == 1000);
        REQUIRE(matr2[2][2] == 1000);
        matr2.insert(matr2.end(), vec.begin(), vec.end());
        REQUIRE(matr2[1][2] == 3);
        REQUIRE(matr2[2][0] == 3);
        REQUIRE(matr2[2][1] == 3);
        REQUIRE(matr2[2][2] == 3);
        REQUIRE(matr2[1][1] == 5);
        REQUIRE(matr2[1][0] == 4);
        matr2.insert(matr2.end(), {1,2});
        REQUIRE(matr2[1][2] == 3);
        REQUIRE(matr2[2][0] == 3);
        REQUIRE(matr2[2][1] == 1);
        REQUIRE(matr2[2][2] == 2);
        matr2.insert(matr2.end(), 0, 314);
        matr2.insert(matr2.end(), vec.begin(), vec.begin());
    }
    SECTION("erase"){
        Matrix<int> matr(3,3);
        matr = {1,1,1,2,2,2,3,3,3};
        auto b = matr.erase(matr.begin()+2);
        REQUIRE(matr[0][2] == 0);
        REQUIRE(b == matr.begin()+3);
        matr.erase(matr.begin(), matr.end());
        for (auto it = matr.begin(); it != matr.end() ; ++it) {
            REQUIRE(*it == 0);
        }
    }
    SECTION("clear"){
        Matrix<int> matr(3,3);
        matr = {1,1,1,2,2,2,3,3,3};
        matr.clear();
        for (int & it : matr) {
            REQUIRE(it == 0);
        }
    }
    SECTION("assign"){
        Matrix<int> matr(3,3);
        matr = {1,1,1,2,2,2,3,3,3};
        std::vector<int> vec = {5,5,5,5,5,5,5,5,5,5};
        matr.assign(vec.begin(), vec.end());
        for (int & it : matr) {
            REQUIRE(it == 5);
        }
        matr.assign({3,3,3});
        REQUIRE(matr[1][2] == 0);
        REQUIRE(matr[2][0] == 3);
        matr.assign(10, -100);
        for (int & it : matr) {
            REQUIRE(it == -100);
        }
    }
    SECTION("front and back"){
        Matrix<int> matr(3,3);
        matr = {1,1,1,2,2,2,3,3,3};
        Matrix<int> cmatr(3,3);
        cmatr = {3,3,3,2,2,2,1,1,1};
        REQUIRE(matr.front() == 1);
        REQUIRE(cmatr.front() == 3);
        REQUIRE(matr.back() == 3);
        REQUIRE(cmatr.back() == 1);
    }
    SECTION("find"){
        Matrix<int> matr(3,3);
        matr = {1,-2,30,-50,1,1,0,2,3};
        std::pair<size_t, size_t> finded = matr.find(1,1,1,std::make_pair(0,0));
        REQUIRE(finded.first == 1);
        REQUIRE(finded.second == 2);
    }
    SECTION("add row and column"){
        Matrix<int> matr(3,3);
        matr.addRow(2);
        REQUIRE(matr.getRows() == 4);
        matr.addCol(2);
        REQUIRE(matr.getCols() == 4);
        REQUIRE(matr[2][2] == 0);
        REQUIRE(matr[0][2] == 0);
    }


    SECTION("Iterator") {
        std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
        Matrix<int> matr(2,3);
        matr = {1,2,3,4,5,6};
        SECTION("Default Construct") {
            Matrix<int>::iterator it;
        }

        SECTION("Copy Construct") {
            Matrix<int>::iterator it = matr.begin();
            Matrix<int>::iterator it1(it);
            REQUIRE(it == it1);
        }

        SECTION("Assign") {
            Matrix<int>::iterator it = matr.begin();
            Matrix<int>::iterator it1 = matr.end();
            it1 = it;
            REQUIRE(it == it1);
        }

        SECTION("Dereference") {
            Matrix<int>::iterator it = matr.begin();
            REQUIRE(*it == matr.front());
        }

        SECTION("Compare") {
            Matrix<int>::iterator it = matr.begin();
            Matrix<int>::iterator it1 = matr.begin();
            Matrix<int>::iterator it2 = matr.end();
            REQUIRE(it == it1);
            REQUIRE(it != it2);
        }

        SECTION("Prefix Inc") {
            Matrix<int>::iterator it1 = matr.begin();
            Matrix<int>::iterator it2 = matr.begin();
            REQUIRE(it1 == it2);
            ++it1;
            REQUIRE(it1 != it2);
            ++it2;
            REQUIRE(it1 == it2);
        }

        SECTION("Postfix Inc") {
            Matrix<int>::iterator it1 = matr.begin();
            Matrix<int>::iterator it2 = matr.begin();
            REQUIRE(it1 == it2);
            it1++;
            REQUIRE(it1 != it2);
            it2++;
            REQUIRE(it1 == it2);
        }

        SECTION("Prefix Dec") {
            Matrix<int>::iterator it1 = matr.begin();
            Matrix<int>::iterator it2 = matr.begin();
            ++it1;
            ++it2;
            REQUIRE(it1 == it2);
            --it1;
            REQUIRE(it1 != it2);
            --it2;
            REQUIRE(it1 == it2);
        }

        SECTION("Postfix Dec") {
            Matrix<int>::iterator it1 = matr.begin();
            Matrix<int>::iterator it2 = matr.begin();
            it1++;
            it2++;
            REQUIRE(it1 == it2);
            it1--;
            REQUIRE(it1 != it2);
            it2--;
            REQUIRE(it1 == it2);
        }
    }


    SECTION("special iterator"){
        Matrix<int> matr(3,3);
        matr = {1,2,3,4,5,6,7,8,9};
        auto it = matr.sbegin(0,0);
        REQUIRE(*it == 1);
        it++;
        it++;
        REQUIRE(*it == 4);
        auto itt = matr.sbegin(1,2);
        REQUIRE(*itt == 2);
        ++itt;
        ++itt;
        REQUIRE(*itt == 5);
        itt++;
        --itt;
        itt--;
        REQUIRE(*itt == 3);
        it = itt;
        REQUIRE(*it == 3);
        REQUIRE(it == itt);
        auto ittt(itt);
        REQUIRE(*ittt == 3);
        *ittt = 33;
        REQUIRE(*ittt == 33);
    }
}