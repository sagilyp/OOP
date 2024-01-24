#include "Game.h"
#include "Construction.h"
#include "Landscape.h"
#include "Enemy.h"
#include <thread>
#include <semaphore>

void Game::uploadInformation(){
    std::fstream fs("../Config/save.json");
    if(fs.is_open()) {
        fs >> save;
        fs.close();
    }
    std::fstream fl("../Config/landscape.json");
    if(fl.is_open()) {
        fl >> landscape;
        fl.close();
    }
    std::fstream flv("../Config/levels.json");
    if(flv.is_open()) {
        flv >> levels;
        flv.close();
    }
    std::fstream fu("../Config/upgrade.json");
    if(fu.is_open()) {
        fu >> upgrade;
        fu.close();
    }
    Construction* llair;
    if(save.empty()){
        size_t h = landscape["1"]["height"];
        size_t w = landscape["1"]["width"];
        land = new Landscape(h, w);
        std::vector<int> vec = landscape["1"]["matrix"];
        auto it2 = land->matrField.begin();
        for (auto it1 = vec.begin(); it1 != vec.end(); ++it1) {
            *it2 = *it1;
            ++it2;
        }
        for (int i = 0; i < land->getH(); ++i) {
            for (int j = 0; j < land->getW(); ++j) {
                if(land->matrField[i][j].getType() == 3){
                    land->matrField[i][j].setType(LandType(2));
                    Construction* lair = new Lair();
                    lair->setLevel(1);
                    dynamic_cast<Lair*>(lair)->setTime(levels["1"]["tbw"]);
                    dynamic_cast<Lair*>(lair)->setCnt(levels["1"]["wave"]);
                    llair = lair;
                    land->build(lair, std::make_pair(i, j));
                }
                if(land->matrField[i][j].getType() == 4){
                    land->matrField[i][j].setType(LandType(2));
                    Construction* castle = new Castle("KAF12", 1000, 1000);
                    land->castlePtr = dynamic_cast<Castle*>(castle);
                    land->build(castle, std::make_pair(i, j));
                }
            }
        }
    }
    for (int i = 0; i < levels["1"]["quantity"]; ++i) {
        Enemy* enm = new Enemy(levels["1"]["type"], levels["1"]["health"], levels["1"]["gold"], levels["1"]["velocity"]);
        dynamic_cast<Lair*>(llair)->pushEnemy(enm);
    }
}


Game::Game(){
    level = 1;
    uploadInformation();
}


template <typename It>
void mv(It begin, It end, Game& gm){
    for (auto it = begin; it != end ; ++it) {
        dynamic_cast<Enemy*>(it->first)->move(gm);
    }
}

void move_mt(Game &gm){
    auto threadNum = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(threadNum);
    auto first = gm.land->enemyLocation.begin(), last = gm.land->enemyLocation.end();
    auto elements = std::distance(first, last);
    for (size_t i = 0; i < threadNum; ++i) {
        size_t start_i = i * elements/ threadNum;
        size_t end_i = (i+1) * elements / threadNum;
        auto start = std::next(first, start_i);
        auto end = std::next(first, end_i);
        threads[i] = std::thread([=, &gm](){mv(start,end, gm);});
    }
    for (auto& thread : threads) {
        thread.join();
    }

}

template <typename It>
void hit(It begin, It end, Game& gm, std::binary_semaphore& sem){
    for (auto it = begin; it != end ;) {
        auto next = std::next(it);
        if(typeid(*it->first).name() == std::string("11SimpleTower") or typeid(*it->first).name() == std::string("10MagicTower")
                            or typeid(*it->first).name() == std::string("9MagicTrap")){
            (dynamic_cast<Tower*>(it->first))->hit_t(*gm.land, sem);
        }
        it = next;
    }
}

void hit_mt(Game &gm){
	std::binary_semaphore sem(1);
    auto threadNum = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(threadNum);
    auto first = gm.land->cnstrLocation.begin(), last = gm.land->cnstrLocation.end();
    auto elements = std::distance(first, last);
    for (size_t i = 0; i < threadNum; ++i) {
        size_t start_i = i * elements/ threadNum;
        size_t end_i = (i+1) * elements / threadNum;
        auto start = std::next(first, start_i);
        auto end = std::next(first, end_i);
        threads[i] = std::thread([=, &gm, &sem](){hit(start,end, gm, sem);});
    }
    for (auto& thread : threads) {
        thread.join();
    }

}

// сходить всем -Ю выпустить новых -Ю выстрелить всем -Ю подействовать эффектами -Ю умереть
void Game::makeMove() {  //утром деньги вечером стулья
    for (auto it = land->cnstrLocation.begin(); it != land->cnstrLocation.end(); ++it) {
        if (typeid(*it->first).name() == std::string("4Lair")) {
            if(dynamic_cast<Lair*>(it->first)->empty()){
                bool flag = it->first->improve(*this);
                if(!flag and land->enemyLocation.empty()){
                    throw std::runtime_error("You win!");
                }
            }

        }
    }
    
    move_mt(*this);

//    for (auto it = land->cnstrLocation.begin(); it != land->cnstrLocation.end(); ++it) {
//        std::cout << it->second.first << ' ' << it->second.second << std::endl;
//        auto bb = (it->first);
//        std::cout << typeid(*bb).name() << std::endl;
//    }
    for (auto it = land->cnstrLocation.begin(); it != land->cnstrLocation.end(); ++it) {
        if(typeid(*it->first).name() == std::string("4Lair")){
            (dynamic_cast<Lair*>(it->first))->releaseEnemy_t(*this);

        }
    }
    hit_mt(*this);
    for(auto it = land->enemyLocation.begin(); it != land->enemyLocation.end(); ++it){
        it->first->effAct();
    }
    for(auto it = land->enemyLocation.begin(); it != land->enemyLocation.end();){
        if(it->first->getCurHealth() <= 0){
            it->first->kill(*land);
            delete it->first;
            it = land->enemyLocation.erase(it);  
            
        }
        else ++it;
    }
    ++time;
}

void Game::towerUpd(const size_t& x, const size_t& y){
    if(land->matrField[x][y].getCnstr() == nullptr or (typeid(*land->matrField[x][y].getCnstr()).name() == "4Lair") or
            (typeid(*land->matrField[x][y].getCnstr()).name() == "6Castle") or land->matrField[x][y].getCnstr()->improve(*this) == false){
        std::cout << "Can not improve tower !" << std::endl;
    }
}

void Game::castleUpd() {
    if(land->castlePtr->improve(*this) == false){
        std::cout << "Can not improve castle !" << std::endl;
    }
}

void Game::build(const size_t& x, const size_t& y, int t_type, int e_type = 1){
    Construction* tower = nullptr;
    if(x*y > land->width*land->height)
        throw std::runtime_error("Out of landscape fields");
    if(land->matrField[x][y].getCnstr() != nullptr){
        std::cout << "Cann't build tower" << std::endl;
        return;
    }
    if(t_type == 3 and land->matrField[x][y].getType() != ROAD){
        std::cout << "Cann't build tower" << std::endl;
        return;
    }
    if((t_type == 2 or t_type == 1) and land->matrField[x][y].getType() != FIELD) {
        std::cout << "Cann't build tower" << std::endl;
        return;
    }
    if(t_type == 1){
        tower = new SimpleTower(*this);
    }
    if(t_type == 2){
        tower = new MagicTower(*this, e_type);
    }
    if(t_type == 3){
        tower = new MagicTrap(*this, e_type);
    }
    land->build(tower, std::make_pair(x, y));
}

void Game::raze(const size_t &x, const size_t& y){
    if(x >= land->width or y >= land->height)
        throw std::runtime_error("Out of landscape fields");
    if(land->matrField[x][y].getCnstr() == nullptr or land->matrField[x][y].getType() == 3 or land->matrField[x][y].getType() == 4){
        std::cout << "Cann't raze tower" << std::endl;
        return;
    }
    land->raze(std::make_pair(x,y));
}

void Game::erase(){
    for (auto it = land->cnstrLocation.begin(); it != land->cnstrLocation.end() ; ++it) {
        delete it->first;
    }
    for (auto it = land->enemyLocation.begin(); it != land->enemyLocation.end() ; ++it) {
        delete it->first;
    }
    //delete land->castlePtr;
}
