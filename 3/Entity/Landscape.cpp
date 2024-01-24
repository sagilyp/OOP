#include "Landscape.h"
#include "Cell.h"
#include "Construction.h"


#include <typeinfo>
#include <vector>
#include <map>
#include <stack>
#include <cmath>

double Landscape::distance(const std::pair<int,int>& cor1, const std::pair<int, int>& cor2) const {
    if((cor1.first or cor2.first) >= height or (cor1.second or cor2.second) >= width)
        throw std::runtime_error("Out of landscape fields");
    std::pair<double,double> vec = {static_cast<double>(cor1.first-cor2.first), static_cast<double>(cor1.second-cor2.second)};
    return sqrt(pow(vec.first, 2) + pow(vec.second, 2));
}

//std::pair<int,int> Landscape::findEnemy(const Enemy& enm){
//    return enmLocation[&enm];
//}
//
//std::pair<int,int> Landscape::findCnstr(const Construction& cnst){
//    return map[&cnst];
//}

bool Landscape::raze(const std::pair<int,int>& cord){
    if(cord.first*cord.second > width*height)
        throw std::runtime_error("Out of landscape fields");
    if(matrField[cord.first][cord.second].getCnstr() == nullptr)
        return false;
    for(auto it = cnstrLocation.begin(); it != cnstrLocation.end(); ++it){
        if(it->second == cord) {
            cnstrLocation.erase(it);
            break;
        }
    }
    matrField[cord.first][cord.second].getCnstr();
    matrField[cord.first][cord.second].setCnstr(nullptr);
    return true;
}

bool Landscape::build(Construction* cnst, std::pair<int,int> cord) {
    if(cord.first*cord.second > width*height)
        throw std::runtime_error("Out of landscape fields");
    if(cnst == nullptr or (typeid(*cnst).name() == std::string("9MagicTrap") and matrField[cord.first][cord.second].getType() != ROAD))
        return false;
    if((typeid(*cnst).name() == std::string("10MagicTower") or typeid(*cnst).name() == std::string("11SimpleTower")) and matrField[cord.first][cord.second].getType() != FIELD)
        return false;
    raze(cord);
    cnstrLocation[cnst] = cord;
    matrField[cord.first][cord.second].setCnstr(cnst);
}

std::pair<int,int> Landscape::findRoad(const std::pair<int,int> &loc, const std::pair<int,int>& trace){
    std::vector<std::pair<int,int>> vec;
    for (auto it = matrField.sbegin(loc.first, loc.second) ; it != matrField.send(loc.first, loc.second); ++it) {
            if(matrField[it.geti()][it.getj()].getType() == ROAD){
                std::pair<int, int> newLoc =  std::make_pair(it.geti(),it.getj());
                if(newLoc != trace and newLoc != loc){
                    vec.push_back(newLoc);
                }
            }
    }
    if(!vec.empty()) {
        std::pair<int, int> res;
        double cmp = std::numeric_limits<double>::max();
        std::pair<int, int> cloc = cnstrLocation[castlePtr];
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (distance(*it, cloc) < cmp) {
                cmp = distance(*it, cloc);
                res = *it;
            }
        }
        return res;
    }
    throw std::runtime_error("Cann't find road");
}

bool Landscape::isTrue(){
    std::cout << "SSSSS\n";
    std::stack<std::pair<int,int>> stack; //стэк клеток для прохождения
    std::pair<int,int> cstLoc = cnstrLocation[castlePtr]; // координаты замка
    std::map<std::pair<int,int>, bool> visited; // таблица посещенных клеток
    std::vector<std::pair<size_t,size_t>> lairLoc; // вектор координат логов
   // lairLoc.
   std::cout << "AB";
    for(auto it = cnstrLocation.begin(); it != cnstrLocation.end(); ++it) {
        try {
            if (typeid(*(it->first)).name() == std::string("4Lair"))
                lairLoc.push_back(it->second); // заполняем вектор координат логов
        }
        catch(...){
            std::cout << lairLoc.size() << std::endl;
        }
    }
    for (auto it = lairLoc.begin(); it != lairLoc.end() ; ++it) {
        std::cout << it->first << it->second << " lairs\n";
    }
    std::cout << "boba\n";
    stack.push(cstLoc);  //положить на стек замок
    while(!stack.empty()){ // пока стек не пуст
        std::pair<int,int> loc = stack.top(); //взять со стека
        std::cout << "curr cell:  " << loc.first << ", " << loc.second << std::endl;
        stack.pop();
        std::cout << "size of stack :  " << stack.size() << std::endl;
        visited[loc] = true; // отметить посещенной
        for (auto it = matrField.sbegin(loc.first, loc.second) ; it != matrField.send(loc.first, loc.second); ++it) {
                std::cout << "i am in cycle!" << "i j "<< it->getType() << std::endl;
                //std::cout << matrField[i][j].getType() << " what "<< (visited[std::make_pair(i,j)] == false) << std::endl;
                if(it->getType() == ROAD and visited[std::make_pair(it.geti(),it.getj())] == false){
                    std::cout << "i j"<< it.geti() << " " << it.getj() << std::endl;
                    std::pair<size_t, size_t> newLoc =  std::make_pair(it.geti(),it.getj());
                    for(auto t = lairLoc.begin(); t != lairLoc.end(); ++t){
                        if(*t == newLoc){
                            std::cout << "deleting lair" << " i j "<< newLoc.first << " " << newLoc.second << std::endl;
                            std::erase(lairLoc, newLoc);
                            //lairLoc.erase(newLoc);
                            for (auto it = lairLoc.begin(); it != lairLoc.end(); ++it) {
                                std::cout << it->first << it->second << '\n';
                            }
                            break;
                        }
                    }
                    std::cout << "aafsff";
                    stack.push(newLoc);
                }
        }
    }
    if(lairLoc.empty())
        return true;
    return false;
}

void Landscape::set(size_t i,size_t j, Cell& cl){
    matrField[i][j] = cl;
    if(cl.getCnstr() != nullptr)
        cnstrLocation[cl.getCnstr()] = std::pair(i,j);
}

Cell& Landscape::get(size_t i, size_t j){
    return matrField[i][j];
}


Landscape::Landscape(const size_t i,const size_t j): height(i), width(j), matrField(i, j) {}

Landscape::Landscape(const Landscape & _land) {
    matrField = _land.matrField;
    height = _land.height;
    width = _land.width;
    castlePtr = new Castle(*_land.castlePtr);
    cnstrLocation = _land.cnstrLocation;
    enemyLocation = _land.enemyLocation;
}



