#include <iostream>
#include "UI.h"
#include "../Utils/getNumber.h"
#include "Game.h"
#include "Landscape.h"
#include "Enemy.h"
#include "Construction.h"

void UI::choose(Game & gm) {
    std::cout << "1 - Make move    2 - Tower update    3 - Castle update   4 - Build     5- Raze    6 - Draw    7 - Exit" << std::endl;
    int i = getNum<int>(1,7);
    switch (i) {
        case 1:{
            gm.makeMove();
            break;
        }
        case 2:{
            std::cout << "What tower do you want to improve(enter coordinates)?" << std::endl;
            int x = getNum<int>(0,gm.land->getH());
            int y = getNum<int>(0,gm.land->getW());
            gm.towerUpd(x,y);
            break;
        }
        case 3:{
            gm.castleUpd();
            break;
        }
        case 4:{
            std::cout << "Where do you want to build(enter coordinates)?" << std::endl;
            int x = getNum<int>(0,gm.land->getH());
            int y = getNum<int>(0,gm.land->getW());
            std::cout << "What kind of construction do you want?\n" << "1 - Simple Tower    2 - Magic Tower    3 - Magic Trap" << std::endl;
            int t_type = getNum<int>(1,3);
            int e_type = 0;
            if(t_type != 1){
                std::cout << "What kind of effect do you want?\n" << "1 - POISONING    2 - WEAKING    3 - SLOWING" << std::endl;
                e_type = getNum<int>(1,3);
            }
            gm.build(x,y,t_type, e_type);
            break;
        }
        case 5:{
            std::cout << "Where do you want to raze(enter coordinates)?" << std::endl;
            int x = getNum<int>(0,gm.land->getH());
            int y = getNum<int>(0,gm.land->getW());
            gm.raze(x,y);
            break;
        }
        case 6:{
            draw(std::cout, *gm.land);
            break;
        }
        case 7:{
            throw std::runtime_error("Exit");
            break;
        }
    }
}

std::ostream& UI::draw(std::ostream& os,Landscape& land){
    for (int i = 0; i < land.getH(); ++i) {
        for (int j = 0; j < land.getW(); ++j) {
            if(land.matrField[i][j].getType() == 0)
                os << "| ";
            if(land.matrField[i][j].getType() == 1) {
                if(land.matrField[i][j].getCnstr() != nullptr and (typeid(*land.matrField[i][j].getCnstr()).name() == std::string("10MagicTower") or
                                                                  typeid(*(land.matrField[i][j].getCnstr())).name() == std::string("11SimpleTower"))) {
                    os << "§ ";
                }
                else
                    os << "- ";
            }
            if(land.matrField[i][j].getType() == 2) {
                if(land.matrField[i][j].getCnstr() != nullptr and typeid(*land.matrField[i][j].getCnstr()).name() == std::string("6Castle")){
                    os << "$ ";
                }
                if(land.matrField[i][j].getCnstr() != nullptr and typeid(*land.matrField[i][j].getCnstr()).name() == std::string("4Lair")){
                    os << "# ";
                }
                else {
                    bool flag = false;
                    for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
                        if (it->second == std::make_pair(i, j)) {
                            os << "@ ";
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        if (land.matrField[i][j].getCnstr() != nullptr and
                            typeid(*land.matrField[i][j].getCnstr()).name() == std::string("9MagicTrap"))
                            os << "~ ";
                        else
                            os << "  ";
                    }
                }
            }
        }
        os << std::endl;
    }
    os << std::endl;
    os << " E n e m y s    L o c a t i o n  :" << std::endl;
    os << " name/ coordinates/ health/ velocity/ gold" << std::endl;
    for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
        os << (it->first->getType() == 0?"goblin":it->first->getType() == 1?"mag":"giant") << "     ";
        os << "(" << it->second.first << ", " << it->second.second << ")     ";
        os << it->first->getCurHealth() << "     ";
        os << it->first->getCurVel() << "     ";
        os << it->first->getGold() << std::endl;
    }
    os << std::endl;
    os << "  C o n s t r u c t i o n s   L o c a t i o n  :" << std::endl;
    for (auto it = land.cnstrLocation.begin(); it != land.cnstrLocation.end() ; ++it) {
        if(typeid(*it->first).name() == std::string("4Lair"))
            os << "Lair";
        if(typeid(*it->first).name() == std::string("11SimpleTower")){
            os << "Simple Tower";
        }
        if(typeid(*it->first).name() == std::string("10MagicTower")){
            os << "Magic Tower";
        }
        if(typeid(*it->first).name() == std::string("9MagicTrap")){
            os << "Magic Trap";
        }
        if(typeid(*it->first).name() == std::string("6Castle")){
            os << "Castle";
        }
        os << " >> " << "[" << it->second.first << ", " << it->second.second << "] " << " level: " << it->first->getLevel() << std::endl;
        if(typeid(*it->first).name() == std::string("11SimpleTower")){
            os << "     radius - " << dynamic_cast<Tower*>(it->first)->getChar("radius") << std::endl;
            os << "     damage - " << dynamic_cast<Tower*>(it->first)->getChar("damage") << std::endl;
            os << "     cost - " << dynamic_cast<Tower*>(it->first)->getChar("cost") << std::endl;
            os << "     radius - " << dynamic_cast<Tower*>(it->first)->getChar("radius") << std::endl;
        }
        if(typeid(*it->first).name() == std::string("10MagicTower") or typeid(*it->first).name() == std::string("9MagicTrap")){
            os << "     radius - " << dynamic_cast<Tower*>(it->first)->getChar("radius") << std::endl;
            os << "     damage - " << dynamic_cast<Tower*>(it->first)->getChar("damage") << std::endl;
            os << "     cost - " << dynamic_cast<Tower*>(it->first)->getChar("cost") << std::endl;
            os << "     radius - " << dynamic_cast<Tower*>(it->first)->getChar("radius") << std::endl;
            os << "     effect action time - " << dynamic_cast<Tower*>(it->first)->getChar("act_time") << std::endl;
            os << "     effect damage - " << dynamic_cast<Tower*>(it->first)->getChar("value") << std::endl;
        }
    }
    os << std::endl;
    os << "  R e s o u r c e s  :" << std::endl;
    os << "Gold - "<<land.castlePtr->getGold() << std::endl;
    os << "MaxStrength - "<<land.castlePtr->getMaxStrength() << std::endl;
    os << "CurStrength - "<<land.castlePtr->getCurStrength() << std::endl;

}
