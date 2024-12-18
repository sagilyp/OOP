#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Entity/Landscape.cpp"
#include "../Entity/Enemy.cpp"
#include "../Entity/Cell.cpp"
#include "../Entity/Construction.cpp"
#include "../Entity/Effect.cpp"
#include "../Entity/Game.cpp"
#include "../Entity/Matrix.h"


TEST_CASE("Landscape"){
    SECTION("constructor") {
        Landscape land;
        REQUIRE(land.getH() == 0);
        REQUIRE(land.getH() == 0);
        Landscape lland(4,5);
        REQUIRE(lland.getH() == 4);
        REQUIRE(lland.getW() == 5);
    }
    SECTION("distance"){
        Landscape land(10,10);
        REQUIRE(land.distance(std::make_pair(1,1), std::make_pair(4,5)) == 5);
    }
    SECTION("build and raze"){
        Landscape land(10,10);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                Cell cl{};
                land.set(i,j,cl);
            }
        }
        for (int i = 0; i < 10; ++i) {
            land.setType(4,i,ROAD);
        }
        for (int i = 0; i < 10; ++i) {
            land.setType(i, 4, ROAD);
        }
        land.castlePtr = new Castle(std::string("KAF12"), 100, 1000);
        land.cnstrLocation[land.castlePtr] = std::make_pair(4,9);
        Construction* l1 = new Lair(5);
        Construction* l2 = new Lair(5);
        Construction* l3 = new Lair(5);
        land.cnstrLocation[l1] = std::make_pair(0,4);
        land.cnstrLocation[l2] = std::make_pair(4,0);
        land.cnstrLocation[l3] = std::make_pair(9,4);
        REQUIRE(land.cnstrLocation.size() == 4);
        REQUIRE(land.findRoad(std::make_pair<int>(4,8), std::make_pair<int>(4,7)) == std::make_pair<int>(4,9));
        Construction* t1 = new SimpleTower();
        land.build(t1, std::make_pair<int>(3,7));
        REQUIRE(land.cnstrLocation.size() == 5);
        REQUIRE(land.cnstrLocation[t1] == std::make_pair<int, int>(3,7));
        land.raze(std::make_pair<int, int>(3,7));
        REQUIRE(land.cnstrLocation.size() == 4);
        Construction* t2 = new SimpleTower();
        Cell cl(FOREST, t2);
        land.set(0,0, cl);
        REQUIRE(land.getType(0,0) == FOREST);
        REQUIRE(land.cnstrLocation.size() == 5);
        //land.isTrue();
        //REQUIRE(land.isTrue() == true);
    }

}

TEST_CASE("Game"){
    SECTION("constructor"){
        Landscape land(10,10);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                Cell cl{};
                land.set(i,j,cl);
            }
        }
        for (int i = 0; i < 10; ++i) {
            land.setType(4,i,ROAD);
        }
        for (int i = 0; i < 10; ++i) {
            land.setType(i, 4, ROAD);
        }
        land.castlePtr = new Castle(std::string("KAF12"), 100, 1000);
        land.cnstrLocation[land.castlePtr] = std::make_pair(4,9);
        Construction* l1 = new Lair(5);
        Construction* l2 = new Lair(5);
        Construction* l3 = new Lair(5);
        land.cnstrLocation[l1] = std::make_pair(0,4);
        land.cnstrLocation[l2] = std::make_pair(4,0);
        land.cnstrLocation[l3] = std::make_pair(9,4);
        Construction* t1 = new SimpleTower();
        land.build(t1, std::make_pair<int>(3,5));
        Game gm{&land};
        REQUIRE(gm.getTime() == 0);
        REQUIRE(gm.getWaveNum() == 0);
        gm.makeMove();
        REQUIRE(gm.getTime() == 1);

    }
}

TEST_CASE("Effect"){
    Effect eff1(POISONING, 3, 5);
    Effect eff2(WEAKING, 3, 15, 50);
    Effect eff3(SLOWING, 3, 15);
    REQUIRE(eff1.getType() ==POISONING);
    REQUIRE(eff2.getActionTime() == 3);
    REQUIRE(eff3.getValuePer() == 15);
    Enemy enm(MAGICIAN, 200, 75, 6);
    eff1.damage(enm);
    REQUIRE(eff1.getActionTime() == 2);
    REQUIRE(enm.getCurHealth() == 195);
    eff2.damage(enm);
    REQUIRE(eff2.getActionTime() == 2);
    REQUIRE(enm.getCurHealth() == 187);
    eff3.damage(enm);
    REQUIRE(eff3.getActionTime() == 2);
    REQUIRE(enm.getCurVel() == 5);
    eff3.damage(enm);
    REQUIRE(eff3.getActionTime() == 1);
    REQUIRE(enm.getCurVel() == 4);
    eff3.damage(enm);
    REQUIRE(eff3.getActionTime() == 0);
    REQUIRE(enm.getCurVel() == 3);
    REQUIRE_THROWS(eff3.damage(enm));
}

TEST_CASE("Enemy"){
    SECTION("constructor"){
        Enemy enm(MAGICIAN, 200, 75, 6);
        REQUIRE(enm.getCurHealth() == 200);
        REQUIRE(enm.getMaxHealth() == 200);
        REQUIRE(enm.getTrace().first == 0);
        REQUIRE(enm.getTrace().second == 0);
        REQUIRE(enm.getCurVel() == 6);
        REQUIRE(enm.getGold() == 75);
        Effect eff1(POISONING, 3, 5);
        Effect eff2(WEAKING, 3, 15, 50);
        Effect eff3(SLOWING, 3, 15);
        enm.pushEff(eff1);
        enm.pushEff(eff2);
        enm.pushEff(eff3);
        enm.effAct();
        REQUIRE(enm.getCurHealth() == 187);
        REQUIRE(enm.getCurVel() == 5);
        enm.effAct();
        REQUIRE(enm.getCurHealth() == 174);
        REQUIRE(enm.getCurVel() == 4);
        enm.effAct();
        REQUIRE(enm.getCurHealth() == 161);
        REQUIRE(enm.getCurVel() == 3);
        enm.effAct();
        REQUIRE(enm.getCurHealth() == 161);
        REQUIRE(enm.getCurVel() == 6);
    }
}

TEST_CASE("Castle"){
    SECTION("constructor"){
        Castle c;
        REQUIRE(c.getGold() == 0);
        REQUIRE(c.getCurStrength() == 0);
        REQUIRE(c.getMaxStrength() == 0);
        Castle cst(std::string("B100"), 500, 1000);
        REQUIRE(cst.getGold() == 500);
        REQUIRE(cst.getCurStrength() == 1000);
        REQUIRE(cst.getMaxStrength() == 1000);
        cst.damage(130,200);
        REQUIRE(cst.getGold() == 370);
        REQUIRE(cst.getCurStrength() == 800);
        REQUIRE(cst.getMaxStrength() == 1000);
        cst.writeOfMoney(100);
        REQUIRE(cst.getGold() == 270);
        cst.writeOfMoney(500);
        REQUIRE(cst.getGold() == 270);
        REQUIRE_THROWS(cst.damage(1000,1000));

    }
}

TEST_CASE("Tower"){
    SECTION("SIMPLE"){
        SimpleTower t;
        t.setChar("cost", 300);
        t.setChar("radius", 4);
        t.setChar("damage", 25);
        t.setChar("rate", 3);
    }
    SECTION("MAGIC"){
        MagicTower t;
        t.setChar("cost", 400);
        t.setChar("radius", 4);
        t.setChar("damage", 50);
        t.setChar("rate", 3);
        t.setChar("effect", 0);
        t.setChar("act_time", 3);
        t.setChar("value", 5);
    }
    SECTION("TRAP"){
        MagicTrap t;
        t.setChar("cost", 500);
        t.setChar("radius", 3);
        t.setChar("damage", 100);
    }
}

TEST_CASE("Lair"){
    SECTION("constructor") {
        Lair l{};
        Lair ll(5);
        REQUIRE(l.getTime() == 0);
        REQUIRE(ll.getTime() == 5);
    }
    SECTION("release") {
        Landscape land(10,10);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                Cell cl{};
                land.set(i,j,cl);
            }
        }
        for (int i = 0; i < 10; ++i) {
            land.setType(4,i,ROAD);
        }
        for (int i = 0; i < 10; ++i) {
            land.setType(i, 4, ROAD);
        }
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                std::cout << land.getType(i,j);
            }
             std::cout << std::endl;
        }
        land.castlePtr = new Castle(std::string("KAF12"), 100, 1000);
        land.cnstrLocation[dynamic_cast<Construction*>(land.castlePtr)] = std::make_pair(4,9);
        Construction* ll = new Lair(5);
        Construction* l2 = new Lair(5);
        Construction* l3 = new Lair(5);
        land.cnstrLocation[l2] = std::make_pair(0,4);
        land.cnstrLocation[ll] = std::make_pair(4,0);
        land.cnstrLocation[l3] = std::make_pair(9,4);


        Enemy enm1(MAGICIAN, 200, 75, 6);
        Enemy enm2(MAGICIAN, 200, 75, 6);
        Enemy enm3(MAGICIAN, 200, 75, 6);
        dynamic_cast<Lair*>(ll)->pushEnemy(&enm1);
        dynamic_cast<Lair*>(ll)->pushEnemy(&enm2);
        dynamic_cast<Lair*>(ll)->pushEnemy(&enm3);
        dynamic_cast<Lair*>(ll)->releaseEnemy(land);
        dynamic_cast<Lair*>(ll)->releaseEnemy(land);
        dynamic_cast<Lair*>(ll)->releaseEnemy(land);
        REQUIRE(dynamic_cast<Lair*>(ll)->releaseEnemy(land) == false);
        REQUIRE(land.enemyLocation[&enm1] == std::make_pair(4,1));
        REQUIRE(land.enemyLocation[&enm2] == std::make_pair(4,1));
        REQUIRE(land.enemyLocation[&enm3] == std::make_pair(4,1));
    }
}

TEST_CASE("Cell"){
    SECTION("constructor"){
        Cell cl1;
        REQUIRE(cl1.getType() == FIELD);
        REQUIRE(cl1.getCnstr() == nullptr);
        Construction* cst = new Castle("B100", 500, 1000);
        Cell cl2(ROAD, cst);
        REQUIRE(cl2.getType() == ROAD);
        REQUIRE(cl2.getCnstr() == cst);
       REQUIRE(dynamic_cast<Castle*>(cl2.getCnstr())->getGold() == 500);
    }
}
