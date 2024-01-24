#include "Enemy.h"
#include "Game.h"
#include "Landscape.h"
#include "Effect.h"
#include "Construction.h"

void Enemy::garbageCollection(std::vector<Effect>& effs){
    for (auto it = effs.begin(); it != effs.end() ; ++it) {
        if(it->getActionTime() <= 0){
            if(it->getType() == SLOWING){
                setCurVel(getMaxVel());
            }
            effs.erase(it);
            --it;
        }
    }
}


void Enemy::pushEff(const Effect& ef){
    if(ef.getActionTime() == 0 or ef.getValuePer() == 0)
        throw std::logic_error("Empty effect");
    effects.push_back(ef);
}
void Enemy::effAct(size_t qnt){
    garbageCollection(effects);
    for (int i = 0; i < effects.size(); ++i) {
        Effect& eff = effects[i];
        if(eff.getValuePer() == 0){
            throw std::logic_error("Empty effect");
        }
        std::cout << "   time ostalos   " << eff.getActionTime() <<std::endl;
        if(eff.getActionTime() == 0) {
            std::cout << "delete effect" << std::endl;
            continue;
        }
        eff.damage(*this);
    }
}

bool Enemy::move(Game& gm) {
    if (gm.getTime() % ((10 - curVelocity)) == 0) {
        std::pair<int, int> enmLocation = gm.land->enemyLocation[this];
        std::pair<int, int> roadLocation = gm.land->findRoad(enmLocation, trace);
        trace = enmLocation;
        gm.land->enemyLocation[this] = roadLocation;
        if (gm.land->distance(roadLocation, gm.land->cnstrLocation[gm.land->castlePtr]) == 0) {
            gm.land->castlePtr->damage(gold, curHealth);
			curHealth = -1;
           // kill(*gm.land);
            //gm.land->enemyLocation[this] = std::make_pair(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
        }
        return true;

    }
    return false;
}

bool Enemy::kill(Landscape& land){
        std::cout << " i am died\n";
        land.castlePtr->fillUp(gold);
        //land.enemyLocation.erase(this);
       // delete this;
        //std::erase(land.enemyLocation, *this);
        return true;
}
