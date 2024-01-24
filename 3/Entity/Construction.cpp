#include "Construction.h"
#include "Game.h"
#include "Enemy.h"
#include "Landscape.h"
#include "Effect.h"

#include <atomic>
#include <semaphore>

    void MagicTower::hit(Landscape& land) {
        std::pair<int,int> cnsLoc= land.cnstrLocation[this];
        for (int i = 0; i < characteristics["rate"]; ++i) {
            Enemy *pEnemy = nullptr;
            double dist = std::numeric_limits<double>::max();
            for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
                if (it->first->getCurHealth() <= 0) {
                   // it->first->kill(land);
                    continue;
                }
                double temp = land.distance(cnsLoc, it->second);
                if (temp <= (double) characteristics["radius"] and temp <= dist) {
                    dist = land.distance(cnsLoc, it->second);
                    pEnemy = it->first;
                }
            }
            if (pEnemy != nullptr) {
                Effect ef(static_cast<EffectType>(characteristics["effect"]), characteristics["act_time"],
                          characteristics["value"]);
                pEnemy->setCurHealth(pEnemy->getCurHealth() - characteristics["damage"]);
                if (pEnemy->getCurHealth() > 0)
                   // pEnemy->kill(land);
               // else
                    pEnemy->pushEff(ef);
            }
            break;
        }
//        for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
//            if (it->first->getCurHealth() <= 0) {
//                it->first->kill(land);
//                continue;
//            }
//            std::pair<int,int> cnsLoc= land.cnstrLocation[this];
//            if(land.distance(cnsLoc, it->second) <= characteristics["radius"]) {
//                Effect ef(static_cast<EffectType>(characteristics["effect"]), characteristics["act_time"],
//                          characteristics["value"]);
//                it->first->setCurHealth(it->first->getCurHealth() - characteristics["damage"]);
//                if(it->first->getCurHealth() <= 0)
//                    it->first->kill(land);
//                else
//                    it->first->pushEff(ef);
//            }
//        }
    }

	void MagicTower::hit_t(Landscape& land, std::binary_semaphore& sem) {
	    std::pair<int,int> cnsLoc= land.cnstrLocation[this];
	        std::vector<Enemy*> enemys_;
	        double dist = std::numeric_limits<double>::max();
	        for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
	            if (it->first->getCurHealth() <= 0) {
	                //it->first->kill(land);
	                continue;
	            }
	            double temp = land.distance(cnsLoc, it->second);
	            if (temp <= (double) characteristics["radius"] and temp <= dist) {
	                dist = land.distance(cnsLoc, it->second);
	                enemys_.push_back(it->first);
	            }
	        }
	        for (int i = 0; i < characteristics["rate"]; ++i) {
	            if (!enemys_.empty() and enemys_[0] != nullptr) {
	                int size = enemys_.size();
	                for (int j = 0; j < size; ++j) {
	                    Enemy* pEnemy = enemys_.back();
	                    enemys_.pop_back();
	                    sem.acquire();
	                    if(pEnemy->getCurHealth() > 0) {
	                        Effect ef(static_cast<EffectType>(characteristics["effect"]), characteristics["act_time"],
	                                  characteristics["value"]);
	                        pEnemy->setCurHealth(pEnemy->getCurHealth() - characteristics["damage"]);
	                        if (pEnemy->getCurHealth() >= 0)
	                            pEnemy->pushEff(ef);
	                    }
	                    sem.release();
	                }
	            }
	        }
	}

    void SimpleTower::hit(Landscape& land) {
    std::cout << "i am hitting\n";
        std::pair<int,int> cnsLoc= land.cnstrLocation[this];
        for (int i = 0; i < characteristics["rate"]; ++i) {
            double dist = std::numeric_limits<double>::max();
            Enemy *pEnemy = nullptr;
            for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
                if (it->first->getCurHealth() <= 0) {
                 //   it->first->kill(land);
                    continue;
                }
                double temp = land.distance(cnsLoc, it->second);
                if (temp <= (double) characteristics["radius"] and temp <= dist) {
                    dist = land.distance(cnsLoc, it->second);
                    pEnemy = it->first;
                }
            }
            if (pEnemy != nullptr) {
                std::cout << " Я  ударяюnтn\n";
                pEnemy->setCurHealth(pEnemy->getCurHealth() - characteristics["damage"]);
                //if (pEnemy->getCurHealth() <= 0)
                   // pEnemy->kill(land);
            }
            break;
        }
//        for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
//            if (it->first->getCurHealth() <= 0) {
//                it->first->kill(land);
//                continue;
//            }
//            std::pair<int,int> cnsLoc= land.cnstrLocation[this];
//            if(land.distance(cnsLoc, it->second) <= characteristics["radius"]) {
//                it->first->setCurHealth(it->first->getCurHealth() - characteristics["damage"]);
//                if(it->first->getCurHealth() <= 0)
//                    it->first->kill(land);
//            }
//        }
    }

void SimpleTower::hit_t(Landscape& land, std::binary_semaphore& sem) {
    std::pair<int,int> cnsLoc= land.cnstrLocation[this];
    std::vector<Enemy*> enemys_;
    double dist = std::numeric_limits<double>::max();
    for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
        if (it->first->getCurHealth() <= 0) {
            //it->first->kill(land);
            continue;
        }
        double temp = land.distance(cnsLoc, it->second);
        if (temp <= (double) characteristics["radius"] and temp <= dist) {
            dist = land.distance(cnsLoc, it->second);
            enemys_.push_back(it->first);
        }
    }
    for (int i = 0; i < characteristics["rate"]; ++i) {
        if (!enemys_.empty() and enemys_[0] != nullptr) {
            int size = enemys_.size();
            for (int j = 0; j < size; ++j) {
                Enemy* pEnemy = enemys_.back();
                enemys_.pop_back();
                sem.acquire();
                if(pEnemy->getCurHealth() > 0) {
                    pEnemy->setCurHealth(pEnemy->getCurHealth() - characteristics["damage"]);
                }
                sem.release();
            }
        }
    }
}	

    void MagicTrap::hit(Landscape& land) {
        std::pair<int,int> cnsLoc= land.cnstrLocation[this];
        std::vector<Enemy*> enemysToDie;
        Effect ef(static_cast<EffectType>(characteristics["effect"]), characteristics["act_time"],
                  characteristics["value"]);
        for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
            if(land.distance(cnsLoc, it->second) <= characteristics["radius"]) {
                enemysToDie.push_back(it->first);
            }
        }
        if(!enemysToDie.empty()) {
            for (auto it = enemysToDie.begin(); it != enemysToDie.end(); ++it) {
                (*it)->setCurHealth((*it)->getCurHealth() - characteristics["damage"]);
                (*it)->pushEff(ef);
            }
            land.raze(cnsLoc);
        }
    }

void MagicTrap::hit_t(Landscape& land, std::binary_semaphore& sem) {
    std::pair<int,int> cnsLoc= land.cnstrLocation[this];
    std::vector<Enemy*> enemysToDie;
    Effect ef(static_cast<EffectType>(characteristics["effect"]), characteristics["act_time"],
              characteristics["value"]);
    for (auto it = land.enemyLocation.begin(); it != land.enemyLocation.end(); ++it) {
        if(land.distance(cnsLoc, it->second) <= characteristics["radius"]) {
            enemysToDie.push_back(it->first);
        }
    }
    if(!enemysToDie.empty()) {
        sem.acquire();
        for (auto it = enemysToDie.begin(); it != enemysToDie.end(); ++it) {
            if((*it)->getCurHealth() > 0) {
                (*it)->setCurHealth((*it)->getCurHealth() - characteristics["damage"]);
                (*it)->pushEff(ef);
            }
        }
        land.raze(cnsLoc);
        sem.release();
    }
}

    SimpleTower::SimpleTower(const Game& gm) {
        size_t cost = gm.getUpgrade()["SimpleTower"][0]["cost"];
        gm.land->castlePtr->writeOfMoney(cost);
        characteristics["cost"] = cost;
        characteristics["radius"] = gm.getUpgrade()["SimpleTower"][0]["radius"];
        characteristics["damage"] = gm.getUpgrade()["SimpleTower"][0]["damage"];
        characteristics["rate"] = gm.getUpgrade()["SimpleTower"][0]["rate"];
        ++level;
    }

    bool SimpleTower::improve(const Game& gm) {
        if(gm.getUpgrade()["SimpleTower"][level] == nullptr)
            return false;
        size_t cost = gm.getUpgrade()["SimpleTower"][level]["cost"];
        cost -= characteristics["cost"];
        if(cost > gm.land->castlePtr->getGold())
            return false;
        gm.land->castlePtr->writeOfMoney(cost);
        characteristics["cost"] = cost + characteristics["cost"];
        characteristics["radius"] = gm.getUpgrade()["SimpleTower"][level]["radius"];
        characteristics["damage"] = gm.getUpgrade()["SimpleTower"][level]["damage"];
        characteristics["rate"] = gm.getUpgrade()["SimpleTower"][level]["rate"];
        ++level;
        return true;
        //if(cash > size_t) return false;
        //обновить таблицу характеристик
        //писать деньги с замка
    }

    MagicTower::MagicTower(const Game & gm, const int& e_type) {
        size_t cost = gm.getUpgrade()["MagicTower"][0]["cost"];
        gm.land->castlePtr->writeOfMoney(cost);
        characteristics["cost"] = cost;
        characteristics["radius"] = gm.getUpgrade()["MagicTower"][0]["radius"];
        characteristics["damage"] = gm.getUpgrade()["MagicTower"][0]["damage"];
        characteristics["rate"] = gm.getUpgrade()["MagicTower"][0]["rate"];
        std::string efftype = std::to_string(e_type-1);
        characteristics["act_time"] = gm.getUpgrade()["Effect"][efftype][0]["time"];
        characteristics["value"] = gm.getUpgrade()["Effect"][efftype][0]["value"];
        ++level;
    }

    bool MagicTower::improve(const Game& gm) {
        if(gm.getUpgrade()["MagicTower"][level] == nullptr)
            return false;
        size_t cost = gm.getUpgrade()["MagicTower"][level]["cost"];
        std::cout << characteristics["cost"] << "  cost  cd\n";
        cost -= characteristics["cost"];
        if(cost > gm.land->castlePtr->getGold())
            return false;
        gm.land->castlePtr->writeOfMoney(cost);
        characteristics["cost"] = cost + characteristics["cost"];
        characteristics["radius"] = gm.getUpgrade()["MagicTower"][level]["radius"];
        characteristics["damage"] = gm.getUpgrade()["MagicTower"][level]["damage"];
        characteristics["rate"] = gm.getUpgrade()["MagicTower"][level]["rate"];
        std::string efftype = std::to_string(characteristics["effect"]);
        characteristics["act_time"] = gm.getUpgrade()["Effect"][efftype][level]["time"];
        characteristics["value"] = gm.getUpgrade()["Effect"][efftype][level]["value"];
        ++level;
        return true;
    }

    MagicTrap::MagicTrap(const Game &gm, const int& e_type) {
        size_t cost = gm.getUpgrade()["MagicTower"][0]["cost"];
        gm.land->castlePtr->writeOfMoney(cost);
        characteristics["cost"] = cost;
        characteristics["radius"] = gm.getUpgrade()["MagicTower"][0]["radius"];
        characteristics["damage"] = gm.getUpgrade()["MagicTower"][0]["damage"];
        std::string efftype = std::to_string(e_type-1);
        characteristics["act_time"] = gm.getUpgrade()["Effect"][efftype][0]["time"];
        characteristics["value"] = gm.getUpgrade()["Effect"][efftype][0]["value"];
        ++level;
    }

    bool MagicTrap::improve(const Game& gm) {
        if(gm.getUpgrade()["MagicTower"][level] == nullptr)
            return false;
        size_t cost = gm.getUpgrade()["MagicTower"][level]["cost"];
        cost -= characteristics["cost"];
        if(cost > gm.land->castlePtr->getGold())
            return false;
        gm.land->castlePtr->writeOfMoney(cost);
        characteristics["cost"] = cost + characteristics["cost"];
        characteristics["radius"] = gm.getUpgrade()["MagicTower"][level]["radius"];
        characteristics["damage"] = gm.getUpgrade()["MagicTower"][level]["damage"];
        std::string efftype = std::to_string(characteristics["effect"]);
        characteristics["act_time"] = gm.getUpgrade()["Effect"][efftype][level]["time"];
        characteristics["value"] = gm.getUpgrade()["Effect"][efftype][level]["value"];
        ++level;
        return true;
    }

    bool Lair::releaseEnemy(Landscape& land) {
        if(enemys.empty())
            return false;
        Enemy* enemy = enemys.front();
        std::cout << enemy << std::endl;
        enemys.pop();
        std::pair<int,int> lairLoc = land.cnstrLocation[this];
        std::cout << "Lair location "<<lairLoc.first << "  "<< lairLoc.second << std::endl;
        std::pair<int,int> enemyLoc = land.findRoad(lairLoc, lairLoc);
        std::cout << "Enemy location "<<enemyLoc.first << "  "<< enemyLoc.second << std::endl;
        enemy->setTrace(lairLoc);
        land.enemyLocation[enemy] = enemyLoc;
        return true;
    }


bool Lair::releaseEnemy_t(const Game& gm) {
    if(gm.getTime()%timeBtwWaves == 0 and !enemys.empty()){
        for (auto i = 0; i < cnt; ++i) {
            releaseEnemy(*(gm.land));
        }
        return true;
    }
    return false;
}

    void Lair::pushEnemy(Enemy* enemy) {
        enemys.push(enemy);
    }

    bool Lair::improve(const Game & gm) {
        ++level;
        std::string lvs = std::to_string(level);
        if(gm.getLevels().find(lvs) == gm.getLevels().end()) {
            --level;
            return false;
        }
        timeBtwWaves = gm.getLevels()[lvs]["tbw"];
        cnt = gm.getLevels()[lvs]["wave"];
        for (int i = 0; i < gm.getLevels()[lvs]["quantity"]; ++i) {
            Enemy* enm = new Enemy(gm.getLevels()[lvs]["type"], gm.getLevels()[lvs]["health"], gm.getLevels()[lvs]["gold"],
                                   gm.getLevels()[lvs]["velocity"]);
            pushEnemy(enm);
        }
        return true;
    }

    bool Castle::improve(const Game& gm) {
        if(gm.getUpgrade()["Castle"][level] == nullptr)
            return false;
        size_t cost = gm.getUpgrade()["Castle"][level]["cost"];
        if(cost > gm.land->castlePtr->getGold())
            return false;
        gm.land->castlePtr->writeOfMoney(cost);
        gm.land->castlePtr->setMaxStrength(gm.getUpgrade()["Castle"][level]["strength"]);
        gm.land->castlePtr->setCurStrength(gm.getUpgrade()["Castle"][level]["strength"]);
        ++level;
        return true;
     //   if(cash > size_t) return false;
        //обновить таблицу характеристик
        //cписать деньги с замка
    }

    bool Castle::writeOfMoney(size_t mn) {
        if(mn > gold)
                    return false;
        std::atomic<int> gold_s;
        gold_s.store(gold);
        gold_s.fetch_sub(mn);
        gold = gold_s.load();
        return true;
    }

    void Castle::fillUp(const size_t& mn){
        std::atomic<int> gold_s;
        gold_s.store(gold);
        gold_s.fetch_add(mn);
        gold = gold_s.load();
    }

    void Castle::damage(size_t money, size_t dmg){
        std::atomic<int> gold_s;
        std::atomic<size_t> strength_s;
        gold_s.store(gold);
        strength_s.store(curStrength);
        gold_s.fetch_sub(money);
        gold = gold_s.load();
        if(dmg >= strength_s.load() or gold_s.load() <= 0) {
            strength_s.store(0);
            curStrength = strength_s.load();
            throw std::runtime_error("Game over!");
        }
        //curStrength -= dmg;
        strength_s.fetch_sub(dmg);
        curStrength = strength_s.load();
    }


