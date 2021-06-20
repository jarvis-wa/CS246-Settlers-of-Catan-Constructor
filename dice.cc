#include "dice.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

Dice::Dice(std::shared_ptr<Strategy> strategy) : _strategy{strategy} { };

void Dice::setStrategy(std::shared_ptr<Strategy> strategy) noexcept {
    this->_strategy = strategy;
}

int Dice::roll() noexcept {
    return this->_strategy->rollDice();
}

LoadDice::LoadDice(int numToRoll): Strategy{"load"} {     // we do not throw exception here
    this->numToRoll = numToRoll;
}

void LoadDice::changeNumToRoll(int inputNum) {
    if (inputNum < 2 || inputNum > 12) {
        throw DiceException(inputNum);  // when a user enter their desire rollNumber, we may throw exception
    } else {
    this->numToRoll = inputNum;
    }
}

int LoadDice::rollDice() noexcept {
    return this->numToRoll;
}

int FairDice::rollDice() noexcept {
    srand(time(NULL));
    int num = rand() % 11 + 2;
    std::cout << "The number you rolled is " << num << std::endl;
    return num;
}

Strategy::Strategy(std::string t): type{t} {}

std::string Strategy::returnType() noexcept{
    return this->type;
}
std::string Dice::returnStrategyType() noexcept {
    return this->_strategy.get()->returnType();
}

FairDice::FairDice(): Strategy{"fair"} {}

/*int main() {

    auto ddice = std::make_shared<Dice>( std::make_shared<LoadDice>(5) );
    std::cout << ddice.get()->roll() << std::endl;

    ddice.get()->setStrategy(std::make_shared<FairDice>());

    std::cout << ddice.get()->roll() << std::endl;

    ddice.get()->setStrategy(std::make_shared<LoadDice>(3));
    std::cout << ddice.get()->roll() << std::endl;
    

} */
