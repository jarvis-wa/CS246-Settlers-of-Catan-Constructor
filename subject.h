#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>
#include <string>
#include <memory>
#include "player.h"
class Observer;

class Subject {
    std::string type;                      // one of veretx, edge, tile
    int pos;                          // store the position on board
    std::vector<Observer*> observers;

  public:
    Subject(std::string t, int p);
    void attach(Observer* o) noexcept;  
    void notifyObservers() noexcept;

    std::string returnType() noexcept;              // return the type
    int returnPos() noexcept;                 // return the position
    virtual std::vector<std::shared_ptr<Player>> getOwnerInfo() noexcept = 0;
};

#endif
