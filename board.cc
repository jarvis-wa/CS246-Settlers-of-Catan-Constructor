#include <iostream>
#include "board.h"
#include <fstream>
#include <sstream>

Board::Board(bool whetherIni, int curTurn, std::vector<int> BInfo, std::vector<int> TInfo, std::vector<int> HInfo,
      std::vector<int> edgeInfo, std::vector<std::pair<int, int>> BoardInfo,
      std::vector<std::vector<int>> playerInfo, int geese){
    
    this->afterRoll = false;
    this->whetherIni = whetherIni;
    this->geese = geese;
    this->td = std::make_shared<TextDisplay>(BoardInfo);
    if (geese != -1){
        this->td.get()->changeGeesePos(geese);
    }

    for (int i = 0; i <= 53; ++i){
        this->v.emplace_back(std::make_shared<Vertex>(i));
        this->v[i].get()->attach(this->td.get());

    }
    this->e.emplace_back(std::make_shared<Edge>(0, v[0], v[1]));
    this->e.emplace_back(std::make_shared<Edge>(1, v[0], v[3]));
    this->e.emplace_back(std::make_shared<Edge>(2, v[1], v[4]));
    this->e.emplace_back(std::make_shared<Edge>(3, v[2], v[3]));
    this->e.emplace_back(std::make_shared<Edge>(4, v[4], v[5]));
    this->e.emplace_back(std::make_shared<Edge>(5, v[2], v[7]));
    this->e.emplace_back(std::make_shared<Edge>(6, v[3], v[8]));
    this->e.emplace_back(std::make_shared<Edge>(7, v[4], v[9]));
    this->e.emplace_back(std::make_shared<Edge>(8, v[5], v[10]));

    int edgeRecorder = 9;
    int edgeRow = 9;
    int edgeCol = 12;
    bool checkR = true;
    int curRVextex = 6;
    int curCVextex = 6;
    while (edgeRecorder <= 62){
        if (checkR){
            this->e.emplace_back(std::make_shared<Edge>(edgeRecorder, v[curRVextex], v[curRVextex + 1]));
            edgeRecorder += 1;
            if (edgeRecorder == edgeCol){
                edgeRow += 7;
                curRVextex += 3;
                checkR = false;
            } else {
                edgeRow += 1;
                curRVextex += 2;
            }
        } else {
            this->e.emplace_back(std::make_shared<Edge>(edgeRecorder, v[curCVextex], v[curCVextex + 6]));
            edgeRecorder += 1;
            curCVextex += 1;
            if (edgeRecorder == edgeRow){
                checkR = true;
                if ((curCVextex / 6) % 2 == 0){
                    edgeCol += 3;
                } else {
                    edgeCol += 4;
                }
            } else {
                edgeCol += 1;
            }
        }
    }

    this->e.emplace_back(std::make_shared<Edge>(63, v[43], v[48]));
    this->e.emplace_back(std::make_shared<Edge>(64, v[44], v[49]));
    this->e.emplace_back(std::make_shared<Edge>(65, v[45], v[50]));
    this->e.emplace_back(std::make_shared<Edge>(66, v[46], v[51]));
    this->e.emplace_back(std::make_shared<Edge>(67, v[48], v[49]));
    this->e.emplace_back(std::make_shared<Edge>(68, v[50], v[51]));
    this->e.emplace_back(std::make_shared<Edge>(69, v[49], v[52]));
    this->e.emplace_back(std::make_shared<Edge>(70, v[50], v[53]));
    this->e.emplace_back(std::make_shared<Edge>(71, v[52], v[53]));

    for (int i = 0; i <= 71; ++i){
        this->e[i].get()->attach(this->td.get());
    }

    for (int i = 0; i <= 18; ++i){
        this->t.emplace_back(std::make_shared<Tile>(BoardInfo.at(i).second, BoardInfo.at(i).first,i));
        this->t[i].get()->attach(this->td.get());
    }

    if (geese != -1){
        this->t[geese].get()->mutateGeese();
    }

    this->v[0].get()->attach(t[0].get());
    this->v[1].get()->attach(t[0].get());
    this->v[3].get()->attach(t[0].get());
    this->v[4].get()->attach(t[0].get());
    this->v[8].get()->attach(t[0].get());
    this->v[9].get()->attach(t[0].get());

    this->v[2].get()->attach(t[1].get());
    this->v[3].get()->attach(t[1].get());
    this->v[7].get()->attach(t[1].get());
    this->v[8].get()->attach(t[1].get());
    this->v[13].get()->attach(t[1].get());
    this->v[14].get()->attach(t[1].get());

    this->v[4].get()->attach(t[2].get());
    this->v[5].get()->attach(t[2].get());
    this->v[9].get()->attach(t[2].get());
    this->v[10].get()->attach(t[2].get());
    this->v[15].get()->attach(t[2].get());
    this->v[16].get()->attach(t[2].get());

    this->v[37].get()->attach(t[16].get());
    this->v[38].get()->attach(t[16].get());
    this->v[43].get()->attach(t[16].get());
    this->v[44].get()->attach(t[16].get());
    this->v[48].get()->attach(t[16].get());
    this->v[49].get()->attach(t[16].get());

    this->v[39].get()->attach(t[17].get());
    this->v[40].get()->attach(t[17].get());
    this->v[45].get()->attach(t[17].get());
    this->v[46].get()->attach(t[17].get());
    this->v[50].get()->attach(t[17].get());
    this->v[51].get()->attach(t[17].get());

    this->v[44].get()->attach(t[18].get());
    this->v[45].get()->attach(t[18].get());
    this->v[49].get()->attach(t[18].get());
    this->v[50].get()->attach(t[18].get());
    this->v[52].get()->attach(t[18].get());
    this->v[53].get()->attach(t[18].get());


    int tileRecorder = 3;
    int gap = 3;
    while (tileRecorder <= 15){
        int topLeft = gap + tileRecorder;
        this->v[topLeft].get()->attach(t[tileRecorder].get());
        this->v[topLeft + 1].get()->attach(t[tileRecorder].get());
        this->v[topLeft + 6].get()->attach(t[tileRecorder].get());
        this->v[topLeft + 7].get()->attach(t[tileRecorder].get());
        this->v[topLeft + 12].get()->attach(t[tileRecorder].get());
        this->v[topLeft + 13].get()->attach(t[tileRecorder].get());
        if (gap == 5 || gap == 8 || gap == 12 || gap == 15){
            gap += 2;
        } else {
            gap += 1;
        }
        ++tileRecorder;
    }

    
    for (int i = 0; i <= 3; ++i){      // create player
        std::map<int, int> house;
        std::vector<int> road;
        auto dice = std::make_shared<Dice>(std::make_shared<LoadDice>());
        std::vector<int> resourceLose;
        this->player.emplace_back(std::make_shared<Player>(0, i, playerInfo[i], house, road, dice, 0, resourceLose));
    }


    this->order = curTurn;

    for (int i = 0; i <= 53; ++i){
        if (BInfo[i] != -1){
            this->v[i].get()->add(this->player[BInfo[i]], true);
            this->player[BInfo[i]].get()->addHouse(i);
        } else if (HInfo[i] != -1){
            this->v[i].get()->add(this->player[HInfo[i]], true);
            this->v[i].get()->levelUp(this->player[HInfo[i]], true);
            this->player[HInfo[i]].get()->addHouse(i);
            this->player[HInfo[i]].get()->addHouse(i);
        } else if (TInfo[i] != -1){
            this->v[i].get()->add(this->player[TInfo[i]], true);
            this->v[i].get()->levelUp(this->player[TInfo[i]], true);
            this->v[i].get()->levelUp(this->player[TInfo[i]], true);
            this->player[TInfo[i]].get()->addHouse(i);
            this->player[TInfo[i]].get()->addHouse(i);
            this->player[TInfo[i]].get()->addHouse(i);
        }
    }

 //   std::cerr << 333 << std::endl;
    
    for (int i = 0; i <= 71; ++i){
        if (edgeInfo[i] != -1){
            this->e[i].get()->add(this->player[edgeInfo[i]], true);
            this->player[edgeInfo[i]].get()->addRoad(i);
        }
    }

    //std::cerr << 444 << std::endl;
}

bool Board::findWhetherIni(){
    return this->whetherIni;
}

bool Board::helpIni(){
    // ask for Input
    int readInNumber;
    std::vector<int> temp;
    this->printBoard();
    for (int i = 0; i < 4; i++) {
        bool checkSuccess = false;
        while (checkSuccess == false){
            std::cout << "Builder " << changePlayerName(this->player[i].get()->returnWho()) << " where do you want to build a basement?" << std::endl;
            std::cout << "> ";
            std::string ss;
            std::cin >> ss;
            std::istringstream iss {ss}; 
            if (iss >> readInNumber && readInNumber >= 0){
                try{
                    try {
                        if (readInNumber > 53){
                            throw BaseNotEnough{};
                        } else {
                            this->v[readInNumber].get()->add(this->player[i], true);
                            this->player[i].get()->addHouse(readInNumber);
                            checkSuccess = true;
                            temp.emplace_back(readInNumber);
                        }
                    } catch (BaseException & b){
                        throw PrintHaveBuilt(temp);
                    }
                } catch (BaseException & bb){
                    bb.print();
                }
            } else {
                if (std::cin.eof()){
                    std::cout << "End of file reached." << std::endl;
                    std::cout << std::endl;
                    return true;
                } else {
                    std::cerr << "ERROR: Builder " << changePlayerName(this->player[i].get()->returnWho()) << " where do you want to build a basement? isn't a valid integer." << std::endl;
                }
            }
        }
    }
    for (int i = 3; i >= 0; i--) {
        bool checkSuccess = false;
        while (checkSuccess == false){
            std::cout << "Builder " << changePlayerName(this->player[i].get()->returnWho()) << " where do you want to build a basement?" << std::endl;
            std::cout << "> ";
            std::string ss;
            std::cin >> ss;
            std::istringstream iss {ss}; 
            if (iss >> readInNumber && readInNumber >= 0){
                try{
                    try {
                        if (readInNumber > 53){
                            throw BaseNotEnough{};
                        }
                        this->v[readInNumber].get()->add(this->player[i], true);
                        this->player[i].get()->addHouse(readInNumber);
                        checkSuccess = true;
                        temp.emplace_back(readInNumber);
                    } catch (BaseException & b){
                        throw PrintHaveBuilt(temp);
                    }
                } catch (BaseException & bb){
                    bb.print();
                }
            } else {
                if (std::cin.eof()){
                    std::cout << "End of file reached." << std::endl;
                    std::cout << std::endl;
                    return true;
                } else {
                    std::cerr << "ERROR: Builder " << changePlayerName(this->player[i].get()->returnWho()) << " where do you want to build a basement? isn't a valid integer." << std::endl;
                }
            }
        }
    }
    return false;
}

void Board::buildRes(int housing){
    if (housing <= 53){
        int curTurn = this->order % 4;
        this->v[housing].get()->add(this->player[curTurn], false);
        this->player[curTurn].get()->addHouse(housing);
    } else {
        throw BaseNotEnough{};
    }
}

void Board::improve(int housing){
    if (housing <= 53){
        int curTurn = this->order % 4;
        this->v[housing].get()->levelUp(this->player[curTurn], false);
        this->player[curTurn].get()->addHouse(housing);
    } else {
        throw CannotImprove{};
    }
}

void Board::buildRoad(int road){
    if (road <= 71){
        int curTurn = this->order % 4;
        this->e[road].get()->add(this->player[curTurn], false);
        this->player[curTurn].get()->addRoad(road);
    } else {
        throw BaseNotEnough{};
    }
}

void Board::trade(int color, int give, int take) noexcept {
    int curTurn = this->order % 4;
    this->player[curTurn].get()->tradeWith(this->player[color], give, take);
}

void Board::checkTrade(int color, int give, int take){
    int curTurn = this->order % 4;
    this->player[curTurn].get()->checkWith(this->player[color], give, take);
}

int Board::roll() noexcept {
    int curTurn = this->order % 4;
    int point =  this->player[curTurn].get()->playDice();
    if (point != 7){
        std::map<int, std::vector<int>> temp = {{0,{0,0,0,0,0}},{1,{0,0,0,0,0}},{2,{0,0,0,0,0}},{3,{0,0,0,0,0}}};
        for (auto loc : this->t){
            if (loc.get()->getValue() == point){
                loc.get()->distributeResource(temp);
            }
        }
        bool anyoneGet = false;
        for (auto p : temp){
            int counter = 0;
            for (auto e : p.second){
                if (e > 0){
                    counter += 1;
                    anyoneGet = true;
                }
            }
            if (counter > 0) {
                std::cout << "Builder " << changePlayerName(p.first) << " gained:" << std::endl;
                for (int i = 0; i <= 4; ++i){
                    if (p.second[i] > 0){
                        std::cout << p.second[i] << " " << changeSourceType(i) << std::endl;
                    }
                }
            }
        }
        if (anyoneGet == false){
            std::cout << "No builders gained resources." << std::endl;
        }
    }
    return point;  // for the case when point = 7
}

bool Board::mutateGeese(int loc) {
    if (loc >= 19 || (loc == this->geese)){  // out of range or try to place at the same place
        throw GeeseCannotMove {};
    } else {
        int curTurn = this->order % 4;
        if (this->geese != -1){
            this->t[this->geese].get()->changeIfHaveGeese(curTurn);
        }
        this->geese = loc;
        return this->t[loc].get()->changeIfHaveGeese(curTurn);
    }
}

void Board::steal(int loc, int victim) {
    int curTurn = this->order % 4;
    this->t[loc].get()->stealResource(this->player[curTurn], this->player[victim]);
}

void Board::printBoard() noexcept{
    this->td.get()->print();
}

void Board::printStatus() noexcept {
    for (int who = 0; who <= 3; ++who){
        std::string playerInfo = changePlayerName(who);
        if (who == 0){
            playerInfo += "  ";
        } else if (who == 1){
            playerInfo += "   ";
        }
        std::cout << "Builder Builder " << playerInfo <<  "  has " << this->player[who].get()->getScore() << " building points, ";
        std::cout << this->player[who].get()->returnSourceAmount(0) << " BRICK, ";
        std::cout << this->player[who].get()->returnSourceAmount(1) << " ENERGY, ";
        std::cout << this->player[who].get()->returnSourceAmount(2) << " GLASS, ";
        std::cout << this->player[who].get()->returnSourceAmount(3) << " HEAT, ";
        std::cout << this->player[who].get()->returnSourceAmount(4) << " WIFI." << std::endl;
    }
}

void Board::printResidence() noexcept {
    int curTurn = this->order % 4;
    std::map<int, int> House = this->player[curTurn].get()->getHouse();
    std::cout << changePlayerName(curTurn) << " has built:" << std::endl;
    for (auto e : House){
        std::cout << e.first << " ";
        int Lv = e.second;
        std::string temp;
        if (Lv == 1){
            temp = "B";
        } else if (Lv == 2){
            temp = "H";
        } else if (Lv == 3){
            temp = "T";
        }
        std::cout << temp << std::endl;
    }
}

bool Board::next() noexcept {
    int curTurn = this->order % 4;
    if (this->player[curTurn].get()->getScore() >= 10){
        std::cout << "Congratulations!! " << changePlayerName(curTurn) << " wins!!" << std::endl;
        return true;
    } else {
        this->order += 1;
        this->td.get()->print();
        std::cout << "Builder " << changePlayerName(this->order % 4) << "'s turn." << std::endl;
        std::cout << "> ";
        return false;
    }
};

void Board::setDice(std::string method, int value) {
    int curTurn = this->order % 4;
    this->player[curTurn].get()->changeStrategy(method, value);
};

void Board::market(int sell, int buy){
    int curTurn = this->order % 4;
    if ( sell == buy){
        throw BuySameResource{};
    }
    if ( this->player[curTurn].get()->returnSourceAmount(sell) < 4){
        throw CannotUseMarket{ changeSourceType(sell) };
    } else {
        this->player[curTurn].get()->setSource(sell, this->player[curTurn].get()->returnSourceAmount(sell) - 4);
        this->player[curTurn].get()->setSource(buy, this->player[curTurn].get()->returnSourceAmount(buy) + 1);
        std::cout << changePlayerName(curTurn) << " gains one " << changeSourceType(buy) << " and loses four " << changeSourceType(sell) << "." << std::endl;
    }
}

void Board::help(bool afterRoll) noexcept {
    if (afterRoll){
        std::cout << "Valid commands:" << std::endl;
        std::cout << "~ board : prints the current board.'" << std::endl;
        std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3.'" << std::endl;
        std::cout << "~ build - road <road#> : attempts to builds the road at <road#>." << std::endl;
        std::cout << "~ build - res <housing#> : attempts to builds a basement at <housing#>." << std::endl;
        std::cout << "~ improve <housing#> : attempts to improve the residence at <housing#>." << std::endl;
        std::cout << "~ trade <colour> <give> <take> : attempts to trade with builder <colour>, giving one resource of type <give> and receiving one resource of type <take>." << std::endl;
        std::cout << "~ market <sell> <buy> : attempts to sell resources on the market, giving four resource of type <sell> and receiving one resource of type <buy>." << std::endl;
        std::cout << "~ next : passes control onto the next builder in the game." << std::endl;
        std::cout << "~ save <file> : saves the current game state to <file>." << std::endl;
        std::cout << "~ help : prints out the list of commands." << std::endl;
    } else {
        std::cout << "Valid commands:" << std::endl;
        std::cout << "~ load : changes current builder's dice type to 'loaded'" << std::endl;
        std::cout << "~ fair : changes current builder's dice type to 'fair'" << std::endl;
        std::cout << "~ roll : rolls the dice and distributes resources." << std::endl;
        std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << std::endl;
        std::cout << "~ help : prints out the list of commands." << std::endl;
    }
}


void Board::save(std::string file) noexcept {
    std::ofstream outfile { file };
    outfile << this->order << std::endl;
    for (int i = 0; i <= 3; ++i){
        std::string temp = "";
        for (int j = 0; j <= 4; ++j){
            temp += std::to_string(this->player[i].get()->returnSourceAmount(j));
            temp += " ";
        }
        temp += "r ";
        for (auto road : this->player[i].get()->getRoad()){
            temp += std::to_string(road);
            temp += " ";
        }
        temp += "h";
        for (auto residence : this->player[i].get()->getHouse()){
            temp += " ";
            temp += std::to_string(residence.first);
            temp += " ";
            int Lv = residence.second;
            std::string saver;
            if (Lv == 1){
                saver = "B";
            } else if (Lv == 2){
                saver = "H";
            } else if (Lv == 3){
                saver = "T";
            }
            temp += saver;
        }
        outfile << temp << std::endl;
    }
    std::string tilesaver = "";
    int geese = -1;
    for (int position = 0; position < 18; ++position){
        tilesaver += std::to_string(this->t[position].get()->findSource());
        tilesaver += " ";
        tilesaver += std::to_string(this->t[position].get()->getValue());
        tilesaver += " ";
        if (this->t[position].get()->getIfHaveGeese()){
            geese = position;
        }
    }
    tilesaver += std::to_string(this->t[18].get()->findSource());
    tilesaver += " ";
    tilesaver += std::to_string(this->t[18].get()->getValue());
    if (this->t[18].get()->getIfHaveGeese()){
        geese = 18;
    }
    outfile << tilesaver << std::endl;

    if (geese != -1){
        outfile << std::to_string(geese) << std::endl;
    }


    std::cout << "Saving to " << file << "..." << std::endl;

}
void Board::readInput(const std::string  s, bool& someWin){
    try{
        std::string c = lowerCase(s);
        if (c == "help" || c == "h") {
            this->help(this->afterRoll);
        std::cout << "Enter a command:" << std::endl;
        std::cout << "> ";
        } else if ((c == "load" || c == "l") && this->afterRoll == false) { 
            this->setDice("load"); // does this function contains the display sentence?: Builder <colour> now has loaded Dice.
            std::cout << "Builder " << changePlayerName(this->order % 4) << " now has loaded Dice." << std::endl;
            
            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";
        } else if ((c == "fair" || c == "f") && this->afterRoll == false) {
            this->setDice("fair"); // does this function contains the display sentence?: Builder <colour> now has fair Dice.
            std::cout << "Builder " << changePlayerName(this->order % 4) << " now has fair Dice." << std::endl;
            
            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";
        } else if ((c == "roll" || c == "r") && this->afterRoll == false) {
            int value;
            if (this->player[this->order % 4].get()->returnDiceType() == "load"){
                std::cout << "Input a roll between 2 and 12:" << std::endl;
                bool success = false;
                while (success == false) {
                    std::cout << "> ";
                    std::string ss;
                    std::cin >> ss;
                    std::istringstream iss {ss}; 
                    if (iss >> value && value >= 0){
                        try{
                            this->setDice(this->player[this->order % 4].get()->returnDiceType(), value);
                            success = true;
                        } catch (BaseException & e){
                            e.print();
                            std::cout << "Input a roll between 2 and 12:" << std::endl;
                        }
                    } else {
                        std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                    }
                }
            } else {
                this->setDice(this->player[this->order % 4].get()->returnDiceType(), value);
            }  
            if (this->roll() == 7) {
                for (auto p : this->player){
                    p.get()->dropSource();
                }
                int value;
                bool success = false;
                bool novictim = false;
                while (success == false) {
                    std::cout << "Choose where to place the GEESE." << std::endl;
                    std::cout << "> ";
                    std::string ss;
                    std::cin >> ss;
                    std::istringstream iss {ss};
                    try{ 
                        if (iss >> value && value >= 0){
                            novictim = this->mutateGeese(value);
                            success = true;
                        } else {
                            throw GeeseInvalidPos{};
                        } 
                    } catch (BaseException & e){
                                e.print();
                    }
                }
                if (novictim == true){
                    std::cout << "Enter a command:" << std::endl;
                    std::cout << "> ";
                    this->afterRoll = true;
                    return;
                }

                while (true){
                    std::cout << "Choose a builder to steal from." << std::endl;
                    std::cout << "> ";
                    std::string save;
                    std::cin >> save;
                    std::string temp = lowerCase(save);
                    try {
                        if ((temp != "0") && (temp != "1") && (temp != "2") && (temp != "3") &&
                            (temp != "blue") && (temp != "red") && (temp != "orange") && (temp != "yellow") &&
                            (temp != "b") && (temp != "r") && (temp != "o") && (temp != "y")){

                            throw InvalidColor{};
                        }
                
                        int person = playerstoi(temp);
                        this->steal(value, person);

                        break;
                    } catch (BaseException & e){
                        e.print();
                    }
                }
            }
            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";
            this->afterRoll = true;

        } else if ((c == "board" || c == "b") && this->afterRoll == true) {
            this->printBoard();

            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if (c == "status" || c == "s") {
            this->printStatus();

            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if ((c == "residences" || c == "res") && this->afterRoll == true) {
            this->printResidence();

            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if ((c == "next" || c == "n") && this->afterRoll == true) {
            someWin = this->next();
            this->afterRoll = false;
        } else if (c == "save" && this->afterRoll == true) {
            std::string temp;
            std::cout << "> ";
            std::cin >> temp;
            this->save(temp);
            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";
        } else if (c == "build" && this->afterRoll == true){
            std::string temp;
            std::cout << "> ";
            std::cin >> temp;
            if (lowerCase(temp) == "res"){
                int value;
                bool success = false;
                while (success == false) {
                    std::string ss;
                    std::cout << "> ";
                    std::cin >> ss;
                    std::istringstream iss {ss}; 
                    if (iss >> value && value >= 0){
                        this->buildRes(value);
                        success = true;
                    } else {
                        std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                    }
                }

                std::cout << "Enter a command:" << std::endl;
                std::cout << "> ";

            } else if (lowerCase(temp) == "road") {
                int value;
                bool success = false;
                while (success == false) {
                    std::string ss;
                    std::cout << "> ";
                    std::cin >> ss;
                    std::istringstream iss {ss}; 
                    if (iss >> value && value >= 0){
                        this->buildRoad(value);
                        success = true;
                    } else {
                        std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                    }
                }

                std::cout << "Enter a command:" << std::endl;
                std::cout << "> ";

            } else {
                throw InvalidCommand{};
            }
        } else if (c == "build-res" && this->afterRoll == true){
            int value;
            bool success = false;
            while (success == false) {
                std::string ss;
                std::cout << "> ";
                std::cin >> ss;
                std::istringstream iss {ss}; 
                if (iss >> value && value >= 0){
                    this->buildRes(value);
                    success = true;
                } else {
                    std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                }
            }

            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if (c == "build-road" && this->afterRoll == true){
            int value;
            bool success = false;
            while (success == false) {
                std::string ss;
                std::cout << "> ";
                std::cin >> ss;
                std::istringstream iss {ss}; 
                if (iss >> value && value >= 0){
                    this->buildRoad(value);
                    success = true;
                } else {
                    std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                }
            }

            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if ((c == "improve" || c == "i") && this->afterRoll == true){
            int value;
            bool success = false;
            while (success == false) {
                std::string ss;
                std::cout << "> ";
                std::cin >> ss;
                std::istringstream iss {ss}; 
                if (iss >> value && value >= 0){
                    this->improve(value);
                    success = true;
                } else {
                    std::cerr << "ERROR:  isn't a valid integer." << std::endl;
                }
            }

            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if ((c == "trade" || c == "t") &&  this->afterRoll == true){
            int playerRecorder;
            std::string save;
            std::cout << "> ";
            std::cin >> save;
            std::string temp = lowerCase(save);
            while ((temp != "0") && (temp != "1") && (temp != "2") && (temp != "3") &&
                   (temp != "blue") && (temp != "red") && (temp != "orange") && (temp != "yellow") &&
                   (temp != "b") && (temp != "r") && (temp != "o") && (temp != "y")){
                std::cerr << "Invalid colour." << std::endl;
                std::cout << "> ";
                std::cin >> save;
                temp = lowerCase(save);
            }
            playerRecorder = playerstoi(temp);

            int firstResource;
            std::cout << "> ";
            std::cin >> save;
            temp = lowerCase(save);
            while ((temp != "0") && (temp != "1") && (temp != "2") && (temp != "3") && (temp != "4") &&
                   (temp != "brick") && (temp != "energy") && (temp != "glass") && (temp != "heat") && (temp != "wifi") &&
                   (temp != "b") && (temp != "e") && (temp != "g") && (temp != "h") && (temp != "w")){
                std::cerr << "Invalid item." << std::endl;
                std::cout << "> ";
                std::cin >> save;
                temp = lowerCase(save);
            }
            firstResource = sourcestoi(temp);

            int secondResource;
            std::cout << "> ";
            std::cin >> save;
            temp = lowerCase(save);
            while ((temp != "0") && (temp != "1") && (temp != "2") && (temp != "3") && (temp != "4") &&
                   (temp != "brick") && (temp != "energy") && (temp != "glass") && (temp != "heat") && (temp != "wifi") &&
                   (temp != "b") && (temp != "e") && (temp != "g") && (temp != "h") && (temp != "w")){
                std::cerr << "Invalid item." << std::endl;
                std::cout << "> ";
                std::cin >> save;
                temp = lowerCase(save);
            }
            secondResource = sourcestoi(temp);


            this->checkTrade(playerRecorder, firstResource, secondResource);

            std::cout << changePlayerName(this->order % 4) << " offers " << changePlayerName(playerRecorder);
            std::cout << " one " << changeSourceType(firstResource) << " for one " << changeSourceType(secondResource) << "." << std::endl;

            while (true){
                std::cout << "Does " << changePlayerName(playerRecorder) << " accept this offer?" << std::endl;
                std::string answer;
                std::cout << "> ";
                std::cin >> answer;
                if (lowerCase(answer) == "yes" || lowerCase(answer) == "y"){
                    this->trade(playerRecorder, firstResource, secondResource);
                    break;
                } else if (lowerCase(answer) == "no" || lowerCase(answer) == "n"){
                    std::cout << changePlayerName(playerRecorder) << " declined the trade." << std::endl;
                    break;
                } else {
                    std::cout << "Invalid command." << std::endl;
                    std::cout << std::endl;
                }
            }
            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";

        } else if ((c == "market" || c == "m") && this->afterRoll == true){
            int firstResource;
            std::string save;
            std::cout << "> ";
            std::cin >> save;
            std::string temp = lowerCase(save);
            while ((temp != "0") && (temp != "1") && (temp != "2") && (temp != "3") && (temp != "4") &&
                   (temp != "brick") && (temp != "energy") && (temp != "glass") && (temp != "heat") && (temp != "wifi") &&
                   (temp != "b") && (temp != "e") && (temp != "g") && (temp != "h") && (temp != "w")){
                std::cerr << "Invalid item." << std::endl;
                std::cout << "> ";
                std::cin >> save;
                temp = lowerCase(save);
            }
            firstResource = sourcestoi(temp);

            int secondResource;
            std::cout << "> ";
            std::cin >> save;
            temp = lowerCase(save);
            while ((temp != "0") && (temp != "1") && (temp != "2") && (temp != "3") && (temp != "4") &&
                   (temp != "brick") && (temp != "energy") && (temp != "glass") && (temp != "heat") && (temp != "wifi") &&
                   (temp != "b") && (temp != "e") && (temp != "g") && (temp != "h") && (temp != "w")){
                std::cerr << "Invalid item." << std::endl;
                std::cout << "> ";
                std::cin >> save;
                temp = lowerCase(save);
            }
            secondResource = sourcestoi(temp);

            this->market(firstResource, secondResource);
            std::cout << "Enter a command:" << std::endl;
            std::cout << "> ";
        } else {
            throw InvalidCommand{};
        }

    } catch (BaseException& e) {
        e.print();
        std::cout << "Enter a command:" << std::endl;
        std::cout << "> ";
    }
}

std::string lowerCase(std::string s){
    std::string temp = "";
    for (auto letter : s){
        if (letter >= 65 && letter <= 90){
            letter += 32;
        }
        temp += letter;
    }
    return temp;
}

int playerstoi(std::string s){
    if (s == "0" || s == "blue" || s == "b"){
        return 0;
    } else if (s == "1" || s == "red" || s == "r"){
        return 1;
    } else if (s == "2" || s == "orange" || s == "o"){
        return 2;
    } else if (s == "3" || s == "yellow" || s == "y"){
        return 3;
    } else {
        return -1;    // error
    }
}

int sourcestoi(std::string s){
    if (s == "0" || s == "brick" || s == "b"){
        return 0;
    } else if (s == "1" || s == "energy" || s == "e"){
        return 1;
    } else if (s == "2" || s == "glass" || s == "g"){
        return 2;
    } else if (s == "3" || s == "heat" || s == "h"){
        return 3;
    } else if (s == "4" || s == "wifi" || s == "w"){
        return 4;
    } else {
        return -1;    // error
    }
}
