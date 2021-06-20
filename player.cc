#include "player.h"

// helper to change source(int) to the corresponding string type
std::string changeSourceType(int source) noexcept {
    if (source == 0) return "BRICK";
    if (source == 1) return "ENERGY";
    if (source == 2) return "GLASS";
    if (source == 3) return "HEAT";
    if (source == 4) return "WIFI";
    else return "PARK";
} 

std::string changePlayerName(int player) noexcept {       // 把tile.h里面的 helper function移到player.cc
    if (player == 0){
        return "Blue";
    } else if (player == 1) {
        return "Red";
    } else if (player == 2) {
        return "Orange";
    }
    return "Yellow";
}

Player::Player(int score, int who, std::vector<int> source, std::map<int, int> house,
                std::vector<int> road, std::shared_ptr<Dice> dice, int sumToLose, std::vector<int> resourceLose) :
    score{score}, who{who}, source{source}, house{house}, road{road}, dice{dice}, sumToLose{sumToLose}, resourceLose{resourceLose} { };


Player::~Player() { };

int Player::returnWho() noexcept { return this->who; }

int Player::returnSourceAmount(int givenSource) noexcept {
    return this->source.at(givenSource);
}

int Player::getScore() noexcept { return this->score; }

std::map<int, int> Player::getHouse() noexcept { return this->house; }

std::vector<int> Player::getRoad() noexcept { return this->road; }
void Player::setSource(int givenSource, int amount) noexcept {
    this->source.at(givenSource) = amount;
}

std::vector<int> Player::sourceInfo() noexcept {
    return this->source;
}

void Player::addRoad(int location) noexcept {        // already a valid location
    this->road.emplace_back(location);
}

// two cases: no such location has house, or the house in a existing location need improving
void Player::addHouse(int location) noexcept {       // already a valid location
    bool ifExist = false;
    this->score += 1;       // note a player who has at least 10 scores ends the game, not sure if we check here or on board
    for (std::map<int, int>::iterator it = this->house.begin(); it != this->house.end(); ++it) {
        if (it->first == location) {
            it->second ++;  // if already exists, we improve that house(assume the improve action is valid)
            ifExist = true;
            break;
        }
    }
    if (ifExist == false) {
        this->house.emplace(location, 1);
    }
}

int Player::playDice() noexcept {        // if player enters "roll", then player rolled the dice
    // srand(time(NULL));
    return this->dice.get()->roll();
}

void Player::changeStrategy(std::string strategy, int changeValue){
    if (strategy == "load") {
        if (changeValue < 2 || changeValue > 12) {
            throw DiceException(changeValue);  // when a user enter their desire rollNumber, we may throw exception
        } else {
            this->dice.get()->setStrategy(std::make_shared<LoadDice>(changeValue));
        }
    } else if (strategy == "fair") {
        this->dice.get()->setStrategy(std::make_shared<FairDice>());
    }
}


int Player::getSumToLose() noexcept { return this->sumToLose; }

std::vector<int> Player::getResourceLose() noexcept { return this->resourceLose; }

void Player::checkWith(std::shared_ptr<Player>& player, int given, int exchange) {
    if (given >=5 ){
        throw NotEnoughItemself(changeSourceType(given));
    } else if (exchange >= 5){
        throw NotEnoughItemother(changePlayerName(player.get()->returnWho()), changeSourceType(exchange));
    }
    if (this->who == player.get()->returnWho()) {      // if trade with himself
        //TradeSelf tradeself{};
        throw TradeSelf{};
    }

    if (given == exchange){
        throw SameItem{};
    }
    // leave the case: if the current player is trading with an invalid player, throw exception to board
    //   because if we call this function, the player is already be created!
    if (this->source.at(given) < 1) {
        throw NotEnoughItemself(changeSourceType(given));
    }
    if (player.get()->sourceInfo().at(exchange) < 1) {
        throw NotEnoughItemother(changePlayerName(player.get()->returnWho()), changeSourceType(exchange));
    }
}

void Player::tradeWith(std::shared_ptr<Player>& player, int given, int exchange) noexcept{
    // if we reach here, it means the proposal begins (unless the one you trade with says "No")
    this->source.at(given) -= 1;    // given - 1
    this->source.at(exchange) += 1;
    player.get()->setSource(given, player.get()->sourceInfo().at(given) + 1);
    player.get()->setSource(exchange, player.get()->sourceInfo().at(exchange) - 1);
    // need to print the sucessful trade messages : *****note that [player] offers [tradeguy] [number] [given] for [number] [take]
    //                                         Does [tradeguy] accept this offer? is printed by the board when proposal set.
    std::cout << changePlayerName(this->who) << " gains one " << changeSourceType(exchange) 
                << " and loses one " << changeSourceType(given) << std::endl;
    std::cout << ", " << changePlayerName(player.get()->returnWho()) << " gains one " << changeSourceType(given) 
                << " and loses one " << changeSourceType(exchange) << std::endl;
    std::cout << "." << std::endl;
} 

std::string Player::returnDiceType() noexcept{
    return this->dice.get()->returnStrategyType();
}

void Player::dropSource() noexcept { // already pass the test
    std::vector<int> originalSource = this->source;
    this->sumToLose = 0;    // when a new turn begins, they are assumed not to lose their sources, 
    this->resourceLose.clear();     // and clear the vector of resourceLose.
    int sumSource = 0;
    for (auto n : this->source) {   // total number of the player's source
        sumSource += n;
    }
    if (sumSource < 10) return;
    int resourceLose = sumSource / 2;       // number of times to drop, each drops withdraw exactly one source
    this->sumToLose = resourceLose;     // set the number of drops to sumToLose
    for (int i = 0; i < resourceLose; i++) {
        srand(time(NULL));
        int indicator = rand() % sumSource;   // we randomly generate number in [0, this->source-1]
        for (auto& everySource : this->source) {
            if (indicator - everySource < 0) {  // we use an indicator generated to minus each source, until the result < 0
                everySource -= 1;
                sumSource -= 1;
                break;
            } else {
                indicator -= everySource;
            }
        }
    }
    //// if we reach here, then the player drops a half of their sources, we need to update resouceLose.
    for (int i = 0; i < 5; i++) {
        int currChange = originalSource.at(i) - this->source.at(i);
        this->resourceLose.emplace_back(currChange);        // note that currChange maybe 0, but not all 0, thus we just need
                                                            // to add a if statement, to print those resourceLose which is non-zero.
    }
    //// we print the lose source messages for each player with sources >= 10 and loses half of their resources
    std::cout << "Builder " << changePlayerName(this->who) << " loses " << this->sumToLose 
                << " resources to the geese. They lose :" << std::endl;
    for (std::vector<int>::iterator it = this->resourceLose.begin(); it != this->resourceLose.end(); ++it) {
        if (*it > 0) {
            std::cout << *it << " " << changeSourceType(it - this->resourceLose.begin()) << std::endl;
        }
    }
}
