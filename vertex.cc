#include <vector>
#include <string>
#include <memory>
#include "vertex.h"
#include "exception.h"


Vertex::Vertex(int pos): Subject{"vertex", pos},
                         houseLv{0}, owner{nullptr},
                         canBuild{true}{
    for (int i = 0; i < 4; ++i){
        this->whoCanBuilt.emplace_back(false);
    }
}

void Vertex::add(std::shared_ptr<Player> p, bool ifInitialize){
    if (ifInitialize){
        if (this->canBuild == false){
            throw BaseNotEnough();
        } else {
            this->houseLv = 1;
            this->owner = p;
            this->canBuild = false;
            this->notifyObservers();
        }
    } else {
        if (p->returnSourceAmount(0) >= 1 &&
            p->returnSourceAmount(1) >= 1 &&
            p->returnSourceAmount(2) >= 1 &&
            p->returnSourceAmount(4) >= 1){   
            // check whether have enough source
            if (this->canBuild == false){
                throw BaseNotEnough();
            } else {                      // no nearby residence
                if (this->whoCanBuilt.at(p->returnWho())){ // has road
                    this->houseLv = 1;
                    this->owner = p;
                    this->canBuild = false;
                } else {
                    throw BaseNotEnough();
                }
            }
        // reset the source. (-1 for each); successfully build
            p->setSource(0, p->returnSourceAmount(0) - 1);
            p->setSource(1, p->returnSourceAmount(1) - 1);
            p->setSource(2, p->returnSourceAmount(2) - 1);
            p->setSource(4, p->returnSourceAmount(4) - 1);

        // notify
            std::cout << "Builder " << changePlayerName(p.get()->returnWho())<< " successfully built a Basement at " << this->returnPos() << "." << std::endl;
            this->notifyObservers();
        } else {
            throw HouseException();   // not enough sources;
        }
    }
} 

void Vertex::levelUp(std::shared_ptr<Player> p, bool ifInitialize){
    if (ifInitialize){
        this->houseLv += 1;
        this->notifyObservers();
    } else {
        if (this->owner == p){
            if (this->houseLv == 1){
                if (p->returnSourceAmount(2) >= 2 &&
                    p->returnSourceAmount(3) >= 3){ // p can improve here
                        this->houseLv += 1;
                        p->setSource(2, p->returnSourceAmount(2) - 2);
                        p->setSource(3, p->returnSourceAmount(3) - 3);
                        this->notifyObservers();
                        std::cout << "Builder " << changePlayerName(p.get()->returnWho())<< " successfully built a House at " << this->returnPos() << "." << std::endl;
                } else{
                    throw UpException();
                }
            } else if (this->houseLv == 2){
                if (p->returnSourceAmount(0) >= 3 &&
                    p->returnSourceAmount(1) >= 2 &&
                    p->returnSourceAmount(2) >= 2 &&
                    p->returnSourceAmount(3) >= 2 &&
                    p->returnSourceAmount(4) >= 1){
                        this->houseLv += 1;
                        p->setSource(0, p->returnSourceAmount(0) - 3);
                        p->setSource(1, p->returnSourceAmount(1) - 2);
                        p->setSource(2, p->returnSourceAmount(2) - 2);
                        p->setSource(3, p->returnSourceAmount(3) - 2);
                        p->setSource(4, p->returnSourceAmount(4) - 1);
                        this->notifyObservers();
                        std::cout << "Builder " << changePlayerName(p.get()->returnWho())<< " successfully built a Tower at " << this->returnPos() << "." << std::endl;
                } else {
                    throw UpException();
                }
            } else if (this->houseLv >= 3){
                throw CannotImproveTower();
            }
        } else {
            throw CannotImprove();
        }
    }
}

void Vertex::notify(Subject &  whoNotified) noexcept{
    if (whoNotified.returnType() == "vertex") {
        this->canBuild = false;   // can no longer build here
    } else if (whoNotified.returnType() == "edge") { 
        this->whoCanBuilt[whoNotified.getOwnerInfo().at(0).get()->returnWho()]
        = true;
    }
}

std::vector<std::shared_ptr<Player>> Vertex::getOwnerInfo() noexcept{
    std::vector<std::shared_ptr<Player>> temp;
    temp.emplace_back(this-> owner);
    return temp; // return a vector with only one element
}

bool Vertex::checkBuild(int player){
    return this->whoCanBuilt.at(player);
}

std::shared_ptr<Player> Vertex::findOwner(){
    return this->owner;
}

bool Vertex::whetherCanBuild(){    // duggggggggg!
    return this->canBuild;
}
