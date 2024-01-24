#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Entity/Landscape.h"
#include "Entity/Game.h"
#include "Entity/Construction.h"
#include "json/single_include/nlohmann/json.hpp"
#include "Entity/UI.h"

using json = nlohmann::json;
int main() {
    Game gm;
    UI marusya;
    while(1) {
        try {
            marusya.choose(gm);
        }
        catch (std::exception &err) {
            gm.erase();
            std::cerr << err.what() << std::endl;
            break;
        }
    }
   // marusya.draw(std::cout, *gm.land);
//    Landscape land;
//    Game gm{&land};
//    json obj;
//
//    Matrix<int> matr(25,25);
//    Matrix<int> mmatr(25,30);
//    for (auto i = matr.begin(); i != matr.end() ; ++i) {
//        *i = 1;
//    }
//    for (int i = 0; i < 9; ++i) {
//        matr[6][i] = 2;
//    }
//    for (int i = 6; i < 18; ++i) {
//        matr[i][8] = 2;
//    }
//    for (int i = 8; i < 20; ++i) {
//        matr[17][i] = 2;
//    }
//    for (int i = 10; i < 18; ++i) {
//        matr[i][19] = 2;
//    }
//    mmatr = matr;
//    for (int i = 19; i < 25; ++i) {
//        matr[10][i] = 2;
//    }
//    for (int i = 19; i < 30; ++i) {
//        mmatr[10][i] = 2;
//    }
//    matr[6][0] = 3;
//    mmatr[6][0] = 3;
//    matr[10][24] = 4;
//    mmatr[10][29] = 4;
//
//    obj["1"]["height"] = 25;
//    obj["1"]["width"] = 25;
//    obj["1"]["matrix"] = matr;
//    obj["2"]["height"] = 25;
//    obj["2"]["width"] = 30;
//    obj["2"]["matrix"] = mmatr;
//
//    std::fstream flds("../Config/test.json");
//    if(flds.is_open()) {
//        std::cout << "opened";
//        flds >> obj;
//        flds.close();
//    }
//    if(obj["abs"] == nullptr)
//        std::cout << "\nno";
//    size_t h = obj["1"]["height"];
//    size_t w = obj["1"]["width"];
//    Matrix<int> matr(h,w);
//    std::vector<int> vec = obj["1"]["matrix"];
//    matr.insert(matr.end(), vec.begin(), vec.end());
//    for (int i = 0; i < 25; ++i) {
//        for (int j = 0; j < 25; ++j) {
//            std::cout << matr[i][j];
//        }
//        std::cout << std::endl;
//    }
//

//    json obj;
//    std::fstream flds("../Config/.json");
//    if(flds.is_open()) {
//        flds >> obj;
//    }
//    flds.close();
//    std::cout << obj["level"][1]["radius"];

//    Landscape land(10,10);
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            Cell cl{};
//            land.set(i,j,cl);
//        }
//    }
//    for (int i = 0; i < 10; ++i) {
//        land.setType(4,i,ROAD);
//    }
//    for (int i = 0; i < 10; ++i) {
//        land.setType(i, 4, ROAD);
//    }
//    for (auto i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            std::cout << land.matrField[i][j].getType() << ' ';
//        }
//        std::cout << std::endl;
//    }
//    Construction* cp = new Castle(std::string("KAF12"), 1000, 1000);
//    land.castlePtr = dynamic_cast<Castle*>(cp);
//    land.cnstrLocation[cp] = std::make_pair(4,9);
//    Construction* l1 = new Lair(5);
//    Construction* l2 = new Lair(5);
//    Construction* l3 = new Lair(5);
//    land.cnstrLocation[l1] = std::make_pair(0,4);
//    land.cnstrLocation[l2] = std::make_pair(4,0);
//    land.cnstrLocation[l3] = std::make_pair(9,4);
//   // std::cout << land.isTrue();
//    Construction* t1 = new MagicTrap();
//    dynamic_cast<Tower*>(t1)->setChar("cost", 300);
//    dynamic_cast<Tower*>(t1)->setChar("radius", 2);
//    dynamic_cast<Tower*>(t1)->setChar("damage", 200);
//    dynamic_cast<Tower*>(t1)->setChar("rate", 4);
//    dynamic_cast<Tower*>(t1)->setChar("effect", POISONING);
//    dynamic_cast<Tower*>(t1)->setChar("act_time", 3);
//    dynamic_cast<Tower*>(t1)->setChar("value", 10);
//    land.build(t1, std::make_pair<int>(4,5));
//    Game gm{&land};
//    Enemy enm1(MAGICIAN, 200, 75, 9);
//    Enemy enm2(MAGICIAN, 200, 75, 9);
//    Enemy enm3(MAGICIAN, 200, 75, 9);
//    Enemy enm4(MAGICIAN, 200, 75, 9);
//    Enemy enm5(MAGICIAN, 200, 75, 9);
//    dynamic_cast<Lair*>(l2)->pushEnemy(&enm1);
//    dynamic_cast<Lair*>(l2)->pushEnemy(&enm2);
//    dynamic_cast<Lair*>(l2)->pushEnemy(&enm3);
//    dynamic_cast<Lair*>(l2)->pushEnemy(&enm4);
//    dynamic_cast<Lair*>(l2)->pushEnemy(&enm5);
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    gm.makeMove();
//    for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
//        std::cout << it->second.first << ' ' << it->second.second << " enms ";
//    }
//    std::cout << std::endl;
//    for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
//        std::cout << it->first->getCurHealth() << ' ' << " health ";
//    }
//    std::cout << std::endl << land.castlePtr->getCurStrength() << " castle " << land.castlePtr->getGold();
//    std::cout << std::endl << land.enemyLocation.size();

    return 0;
}
