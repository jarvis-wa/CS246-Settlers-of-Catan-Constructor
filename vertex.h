#ifndef __VERTEX_H__
#define __VERTEX_H__
#include "observer.h"
#include "subject.h"

class Vertex: public Subject, public Observer{
    int houseLv;                      // Lv of the residence(if built)
                                      // 0 otherwise;

    std::shared_ptr<Player> owner;    // pointer to the owner(if built)
                                      // nullptr otherwise;

    bool canBuild;                    // true if no residence around
                                      // false otherwise;

    std::vector<bool> whoCanBuilt;    // list of Bool represents which player
                                      // can be built

    public:
    Vertex (int pos);
    void add(std::shared_ptr<Player> p, bool ifInitialize); // true: begin / false: during
    void levelUp(std::shared_ptr<Player> p, bool ifInitialize);
    void notify(Subject & whoNotified) noexcept override;
    std::vector<std::shared_ptr<Player>> getOwnerInfo() noexcept override;
    bool checkBuild(int player);
    std::shared_ptr<Player> findOwner();

    bool whetherCanBuild(); // duggggggggg!

};

#endif
