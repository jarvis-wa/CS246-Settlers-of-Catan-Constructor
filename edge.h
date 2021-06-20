#ifndef __EDGE_H__
#define __EDGE_H__
#include "observer.h"
#include "subject.h"
#include <map>

#include "vertex.h"
#include "tile.h"

class Edge: public Subject{
    Vertex* oneSide;
    Vertex* anotherSide;
    std::shared_ptr<Player> owner;

    public:
    Edge(int pos, std::shared_ptr<Vertex> one, std::shared_ptr<Vertex> another); // also do attach
    void add(std::shared_ptr<Player> p, bool ifInitialize);
    std::vector<std::shared_ptr<Player>> getOwnerInfo() noexcept override;

    //debug!!!!!!!!
    Vertex* returnOneside();
    Vertex* returnAnotherside();
};

#endif
