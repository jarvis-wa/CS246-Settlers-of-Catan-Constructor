#include "tile.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "exception.h"


Tile::Tile(int value, int source, int pos): Subject{"tile", pos},
                                            ifHaveGeese {false},
                                            value {value}, source {source}{}

void Tile::notify(Subject & whoNotified) noexcept {
    if (whoNotified.returnType() == "vertex") { // notified by a vertex
        this->players.emplace_back(whoNotified.getOwnerInfo().at(0));
    }
}

std::vector<std::shared_ptr<Player>> Tile::getOwnerInfo() noexcept {
    return this->players; // return a vector with only one element
}

bool Tile::getIfHaveGeese() noexcept {
    return this->ifHaveGeese;
}

int Tile::getValue() noexcept {
    return this->value;
}

// std::vector<std::shared_ptr<Player>> Tile::getVictims() noexcept {
//     return this->victims;
// }

int Tile::findSource() noexcept {
    return this->source;
}

bool Tile::changeIfHaveGeese(int thief) noexcept {
    if (this->ifHaveGeese == true) {      // change from have to not have geese
        this->ifHaveGeese = false;
        return false;  //useless
    } else {
        std::map<int, int> temp;
        for (auto p : this->players) {               // add any player that is not a thief
            if (p.get()->returnWho() != thief) {
                int sum = 0;
                for (int i = 0; i < 5; ++i){
                    sum += p->returnSourceAmount(i);
                }
                if (sum != 0){          // check have at least one resource
                    bool finder = false;
                    for (auto t : temp){
                        if (t.first == p.get()->returnWho()){
                            finder = true;
                        }
                    }
                    if (finder == false){  // new victim
                        temp.emplace(p.get()->returnWho(), 0);
                    }
                }
            }
        }

        this->ifHaveGeese = true;         // valid tile to place geese
        this->victims = temp;              // reset the victims

        if (temp.size() == 0){                       // no available player to steal
            std::cout << "Builder " << changePlayerName(thief) << " has no builders to steal from." << std::endl;
            this->notifyObservers();
            return true;
        }

        std::cout << "Builder " << changePlayerName(thief) << " can choose to steal from ";
        int length = this->victims.size();
        for (auto p : this->victims){
            if (length > 1){
                std::cout << changePlayerName(p.first) << ", ";
                length -= 1;
            } else {
                std::cout << changePlayerName(p.first) << "." << std::endl;
            }
        }
 
        this->notifyObservers();
        return false;
    }
}

void Tile::stealResource(std::shared_ptr<Player> thief, std::shared_ptr<Player> victim) {
    bool findVictim = false;
    for (auto finder : this->victims){
        if (victim.get()->returnWho() == finder.first){
            findVictim = true;
        }
    }
    if (findVictim == false){
        throw CanNotSteal{};
    } else {

        // std::map<int, int>::iterator v =
        // std::find_if(this->victims.begin(),
        //                 this->victims.end(),
        //                 [victim](std::pair<int,int> thisPlayer) {return thisPlayer.first == victim;}); // find victim

        int sum = 0;
        for (int i = 0; i < 5; ++i){
            sum += victim.get()->returnSourceAmount(i);
        }

        std::srand(std::time(nullptr));
        int randAmount = std::rand() % sum;

        // randomly generate a number between 0 ~ sum - 1

        // first: choose which resource
        int s;
        for (int i = 0; i < 5; ++i){
            randAmount -= victim.get()->returnSourceAmount(i);
            if (randAmount < 0){
                s = i;
                break;
            }
        }

        // second: change victim resource
        victim.get()->setSource(s, victim.get()->returnSourceAmount(s) - 1);
        // last: change thief resource
        thief.get()->setSource(s, thief.get()->returnSourceAmount(s) + 1);

        std::cout << "Builder " << changePlayerName(thief.get()->returnWho());
        std::cout << " steals " << changeSourceType(s) << " from builder ";
        std::cout << changePlayerName(victim.get()->returnWho()) << "." << std::endl;
    }

}

void Tile::distributeResource(std::map<int, std::vector<int>>& temp) noexcept {
    if (this->ifHaveGeese == false && this->source != 5 && this->players.size() != 0){
        for (auto p : this->players) {
            p.get()->setSource(this->source, p.get()->returnSourceAmount(this->source) + 1);
            temp[p.get()->returnWho()][this->source] += 1;
        }
    } 
}

void Tile::mutateGeese(){
    this->ifHaveGeese = true;
}
