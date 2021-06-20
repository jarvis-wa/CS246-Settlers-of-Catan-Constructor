#include "exception.h"
#include <ostream>


std::ostream& operator<<(std::ostream &out, std::vector<int>& haveBuilt) {
    if (haveBuilt.size() == 0) {
        std::cout << std::endl;
        return out;
    } else {
        const int last = haveBuilt.back();
        for (std::vector<int>::iterator it = haveBuilt.begin(); it != haveBuilt.end()-1; ++it) {
            std::cout << *it << ",";
        }                               // eg. this will print (1,2,3,4,
        std::cout << last << std::endl;;
        return out;
    }
}

void BaseNotEnough::print() {
    std::cout << "You cannot build here." << std::endl;
}

PrintHaveBuilt::PrintHaveBuilt(std::vector<int>& v) : haveBuilt{v} { }; // constructors

void PrintHaveBuilt::setHaveBuilt(int res) {
        this->haveBuilt.emplace_back(res);
}

void PrintHaveBuilt::print() {
    BaseNotEnough B;
    B.print();
    std::cout << "Basement already exist as locations: " << this->haveBuilt;
    // need follow by a vector of vertex (23,45,67,...) that represents those
    // already with house (overloading <<)
}

/************************************************/

void CannotImprove::print() {
    std::cout << "Invalid residence." << std::endl;
}

void CannotImproveTower::print() {
    std::cout << "You can't improve that building." << std::endl;
}

void EdgeException::print() {
    std::cout << "You do not have enough resources." << std::endl;
    std::cout << "The cost of a Road is one Heat and one WIFI resource." << std::endl;
}

void HouseException::print() {
    std::cout << "You do not have enough resources." << std::endl;
    std::cout << "The cost of a basement is one Brick, ";
    std::cout << "one Energy, one Glass, and one Wifi resource." << std::endl;
}

void UpException::print() {
    std::cout << "You do not have enough resources." << std::endl;
    std::cout << "The cost to improve a Basement to a House is two GLASS and three HEAT resource." << std::endl;
    std::cout << "The cost to improve a House to a Tower is three BRICK, ";
    std::cout << "two ENERGY, two GLASS, one WIFI, and two HEAT." << std::endl;
}

/************************************************/

void InvalidCommand::print() {
    std::cout << "Invalid command." << std::endl;
    std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
}

void InvalidColor::print() {
    std::cout << "Invalid colour." << std::endl;
}

void InvalidItem::print() {
    std::cout << "Invalid item." << std::endl;
}

void SameItem::print() {
    std::cout << "Why are you trading for the same resource..." << std::endl;
}

NotEnoughItemother::NotEnoughItemother(std::string player, std::string source) :
    player{player}, source{source} { };

void NotEnoughItemother::print() {
    // first need to print the player(either "You" or the one you trade with)
    std::cout << this->player << " doesn't have enough " << this->source << "." << std::endl;
}

NotEnoughItemself::NotEnoughItemself(std::string source) : source{source} { };

void NotEnoughItemself::print() {
    std::cout << "You don't have enough " << this->source << "." << std::endl;
}

void TradeSelf::print() {
    std::cout << "Can't trade with yourself." << std::endl;
}

DeclineTrade::DeclineTrade(std::string tradeWith) : tradeWith{tradeWith} { };

void DeclineTrade::print() {
    std::cout << this->tradeWith << " declined this trade." << std::endl;
}

/****************************************/

DiceException::DiceException(int rollNumber) : rollNumber{rollNumber} { };

void DiceException::print() {
    std::cout << "Invalid roll " << this->rollNumber << "." << std::endl;
}

void RollInvalidNum::print() {
    std::cout << "ERROR:  " << "isn't a valid integer." << std::endl;
}

/****************************************/

void GeeseCannotMove::print() {
    std::cout << "Geese can't move here." << std::endl;
}

GeeseCannotSteal::GeeseCannotSteal(std::string currBuilder) : currBuilder{currBuilder} { };

void GeeseCannotSteal::print() {
    std::cout << "Builder " << this->currBuilder << " has no builders to steal from." << std::endl;
}

void GeeseInvalidPos::print() {
    std::cout << "ERROR: " << "Choose where to place the GEESE. isn't a valid integer." << std::endl;
}

FormatIncorrect::FormatIncorrect(std::string fileName) : fileName{fileName} { };

void FormatIncorrect::print() {
    std::cout << "ERROR: " << this->fileName << " has an invalid format." << std::endl;
}

UnableOpen::UnableOpen(std::string fileName) : fileName{fileName} { };

void UnableOpen::print() {
    std::cout << "ERROR: Unable to open file " << this->fileName << " for board layout." << std::endl;
}

void LoadingWrong::print() {
    std::cout << "Something went wrong when loading" << std::endl;
}

void LoadMissFile::print() {
    std::cout << "ERROR: -load missing filename argument" << std::endl;
}

void BoardMissFile::print() {
    std::cout << "ERROR: -board missing filename argument" << std::endl;
}

void SeedMissNumber::print() {
    std::cout << "ERROR: -seed missing valid seed argument" << std::endl;
}

RandomBoardMiss::RandomBoardMiss(std::string argument) : argument{argument} {};

void RandomBoardMiss::print() {
    std::cout << "ERROR: Unrecognized argument " << this->argument << std::endl;
}

void CanNotSteal::print() {
    std::cout << "They can't be stolen from." << std::endl;
}

CannotUseMarket::CannotUseMarket(std::string s): sell{s} {}

void CannotUseMarket::print() {
    std::cout << "You do not have enough resources." << std::endl;
    std::cout << "You don't have enough " << this->sell << ". You need 4." << std::endl;
}

void BuySameResource::print() {
    std::cout << "Why are you buying the same resource?" << std::endl;
}

BoardAlreadySpecify::BoardAlreadySpecify(std::string type): type{type} {};

void BoardAlreadySpecify::print() {
    std::cout << "ERROR: already specified -board, can't also specify " << this->type << std::endl;
}

AlreadySpecify::AlreadySpecify(std::string type): type{type} {};

void AlreadySpecify::print() {
    std::cout << "ERROR: already spceified " << this->type << " once before" << std::endl;
}

LoadAlreadySpecify::LoadAlreadySpecify(std::string type): type{type} {};

void LoadAlreadySpecify::print() {
    std::cout << "ERROR: already specified -load, can't also specify " << this->type << std::endl;
}
