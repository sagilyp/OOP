#include "Effect.h"
#include "Enemy.h"


    bool Effect::damage(Enemy& enemy) {
//        if(enemy.getCurHealth() <= 0){
//            throw std::logic_error("Enemy is death now!");
//        }
        if(actionTime <= 0){
            throw std::logic_error("Effect is end!");
        }
        switch(type) {
            case POISONING:{
                int _health = enemy.getCurHealth() - static_cast<int>(valuePer);
                std::cout << "this is poisoning eff\n";
                enemy.setCurHealth(_health);
                break;
            }
            case WEAKING:{
                int _health = enemy.getCurHealth() - qnt*(static_cast<double>(valuePer)/100);
                std::cout << "this is weaking eff\n";
                enemy.setCurHealth(_health);
                break;
            }
            case SLOWING:{
                size_t _velocity = enemy.getCurVel()*(1 - static_cast<double>(valuePer)/100); // скорость уменьшается, замедление увеличивается
                std::cout << "this is slowing eff\n";
                enemy.setCurVel(_velocity);
                break;
            }
            default:{
                throw std::runtime_error("There is no such effect.");
            }
        }
        --actionTime;
        return true;
    }


