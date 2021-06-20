#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <map>
#include "dice.h"
#include <memory>
#include "exception.h"

class Dice;
class Strategy;

class Player {
    private:
        int score;
        int who;
        std::vector<int> source;
        std::map<int, int> house;
        std::vector<int> road;
        std::shared_ptr<Dice> dice;
        int sumToLose = 0;
        std::vector<int> resourceLose;  // a vector of the difference of the corresponding resource before drop and after drop
    public:
        Player(int, int, std::vector<int>, std::map<int, int>, std::vector<int>, std::shared_ptr<Dice>, int, std::vector<int>); // constructor
        ~Player();
        int returnWho() noexcept;
        int returnSourceAmount(int givenSource) noexcept; 
        int getScore() noexcept;
        int playDice() noexcept;
        void changeStrategy(std::string, int changeValue = 2) ;   // the input passed as the parameter string

        int getSumToLose() noexcept;     /////
        std::vector<int> getResourceLose() noexcept; ///////
        std::map<int, int> getHouse() noexcept;
        std::vector<int> getRoad() noexcept;
        void setSource(int givenSource, int amount) noexcept;    // set the givenSource value be amount
        std::vector<int> sourceInfo() noexcept;
        void addRoad(int location) noexcept;
        void addHouse(int location) noexcept;
        void checkWith(std::shared_ptr<Player>& player, int given, int exchange); // may throw exception
        void tradeWith(std::shared_ptr<Player>& player, int given, int exchange) noexcept;
        void dropSource() noexcept;      // if the geese activates, any player with 10 or more than 10 sources should drop a half
        std::string returnDiceType() noexcept;
};

// declaration of helper function
std::string changeSourceType(int source) noexcept;

std::string changePlayerName(int player) noexcept;

#endif
