#ifndef __DICE_H__
#define __DICE_H__

#include <memory>
#include "exception.h"

class Strategy {
    std::string type;
    public:
        std::string returnType() noexcept;
        Strategy(std::string t);
        virtual ~Strategy() { };
        virtual int rollDice() = 0; 
};


class Dice {
    private:
        std::shared_ptr<Strategy> _strategy;
    public:
        std::string returnStrategyType() noexcept;
        Dice(std::shared_ptr<Strategy>);
        ~Dice() { };
        void setStrategy(std::shared_ptr<Strategy>) noexcept;
        int roll() noexcept;
};


class LoadDice : public Strategy {
    private:
        int numToRoll;      // the input that the player enters
    public:
        ////// add a mutator to change the roll number ----------------<>
        void changeNumToRoll(int inputNum);
        LoadDice(int num = 1) ;      // set the default rollnumber -1
        int rollDice() noexcept override;
};

class FairDice : public Strategy {
    public:
        FairDice();
        int rollDice() noexcept override;
};

#endif
