#include <map>
#include <string>
#include <memory>
#include "algorithm"
#include "edge.h"
#include "exception.h"

Edge::Edge(int pos, std::shared_ptr<Vertex> one, std::shared_ptr<Vertex> another): 
    Subject{"edge", pos}, oneSide{one.get()}, anotherSide{another.get()}, owner{nullptr} {
    this->attach(this->oneSide);
    this->attach(this->anotherSide);
    this->oneSide->attach(this->anotherSide);
    this->anotherSide->attach(this->oneSide);
}

void Edge::add(std::shared_ptr<Player> p, bool ifInitialize){

    //std::cerr << p.get()->returnWho() << ": ";
    if (ifInitialize){
        this->owner = p;
        this->notifyObservers();
    } else {
        if (p.get()->returnSourceAmount(3) >= 1 &&
            p.get()->returnSourceAmount(4) >= 1){
            if (this->owner != nullptr){      // aleady built
                throw BaseNotEnough();
            } else{
                bool checkValid = false;
                if (this->oneSide->findOwner() == nullptr){  // no one has built
                    if (this->oneSide->checkBuild(p.get()->returnWho())){
                        // havs road
                        checkValid = true;
                    }
                } else if (this->oneSide->getOwnerInfo().at(0) == p){
                    checkValid = true;
                }

                if (this->anotherSide->findOwner() == nullptr){  // no one has built
                    if (this->anotherSide->checkBuild(p.get()->returnWho())){
                        // havs road
                        checkValid = true;
                    }
                } else if (this->anotherSide->getOwnerInfo().at(0) == p){
                    checkValid = true;
                }

                if (checkValid == true){
                    this->owner = p;
                } else {
                    throw BaseNotEnough();
                }
            }

            p.get()->setSource(3, p.get()->returnSourceAmount(3) - 1);
            p.get()->setSource(4, p.get()->returnSourceAmount(4) - 1);

            // notify
            this->notifyObservers();
            std::cout << "Builder " << changePlayerName(p.get()->returnWho())<< " successfully built a Road at " << this->returnPos() << "." << std::endl;
            //std::cerr << std::endl;
        } else {
            throw EdgeException(); 
        }
    }
}


std::vector<std::shared_ptr<Player>> Edge::getOwnerInfo() noexcept{
    std::vector<std::shared_ptr<Player>> temp;
    temp.emplace_back(this-> owner);
    return temp; // return a vector with only one element
}


Vertex* Edge::returnOneside(){
    return this->oneSide;
}
Vertex* Edge::returnAnotherside(){
    return this->anotherSide;
}
