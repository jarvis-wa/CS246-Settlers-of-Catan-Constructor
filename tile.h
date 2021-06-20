#ifndef __TILE_H__
#define __TILE_H__

#include "observer.h"
#include "subject.h"

/*enum class SOURCE {
    // tile types
    BRICK = 0,
    ENERGY = 1,
    GLASS = 2,
    HEAT = 3,
    WIFI = 4,
};*/

class Tile : public Subject, public Observer {
    bool ifHaveGeese;
    int value;
    int source;
    std::vector<std::shared_ptr<Player>> players;

    std::map<int, int> victims; //second element is useless
    
    public:
    Tile(int value, int source, int pos);

    void notify(Subject & whoNotified) noexcept override;
    std::vector<std::shared_ptr<Player>> getOwnerInfo() noexcept override;

    bool getIfHaveGeese() noexcept;
    int getValue() noexcept;
    //std::vector<std::shared_ptr<Player>> getVictims() noexcept;
    int findSource() noexcept;

    bool changeIfHaveGeese(int thief) noexcept;
    void stealResource(std::shared_ptr<Player> thief, std::shared_ptr<Player> victim);
    void distributeResource(std::map<int, std::vector<int>>& temp) noexcept;
    void mutateGeese();
};

#endif
