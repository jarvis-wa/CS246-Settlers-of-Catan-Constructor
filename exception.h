#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include <iostream>
#include <vector>

// used to help printHaveBuilt() to print those vertice which already with house on.
std::ostream& operator<<(std::ostream &out, std::vector<int>& haveBuilt);

class BaseException {       // this is the parent class for all the following classes
    public:
        virtual void print() = 0;   // need override
};

// ******During the Game Turn******, throwed when building houses or roads on an invalid vertex
class BaseNotEnough : public BaseException {
    public:
        BaseNotEnough() {};
        void print() override;
};

// *****At the beginning of the game*****, when a builder tries to build residence on an invalid vertex
class PrintHaveBuilt : public BaseException {
    private:
        std::vector<int> haveBuilt;
    public:
        PrintHaveBuilt( std::vector<int>& );    // customized contructors
        void setHaveBuilt( int );   // push the vertex which is going to be built to the vector haveBuilt
        void print() override;
};

// throwed when trying to improve a invalid residence
class CannotImprove : public BaseException {
    public:
        CannotImprove() {};
        void print() override;
};

// throwed when trying to improve a tower
class CannotImproveTower : public BaseException {
    public:
        CannotImproveTower() {};
        void print() override;
};

// throwed when do not have enough resources to build road
class EdgeException : public BaseException {
    public:
        EdgeException() {};
        void print() override;
};

// throwed when do not have enough resources to build house
class HouseException : public BaseException {
    public:
        HouseException() {};
        void print() override;
};

// throwed when do not have enough resource to improve a valid residence
class UpException : public BaseException {
    public:
        UpException() {};
        void print() override;
};

// throwed when trading with a player but the one you trade with do not have enough source
class NotEnoughItemother : public BaseException {
    private:
        std::string player;
        std::string source;
    public:
        NotEnoughItemother(std::string, std::string);
        void print() override;
};

// throwed when you don't have enough source
class NotEnoughItemself : public BaseException {
    private:
        std::string source;
    public:
        NotEnoughItemself(std::string);
        void print() override;
};

// throwed when the command is invalid
class InvalidCommand : public BaseException {
    public:
        InvalidCommand() {};
        void print() override;
};

// throwed when trading with an invalid player(color)
class InvalidColor : public BaseException {
    public:
        InvalidColor() {};
        void print() override;
};

// throwed when one trading item is invalid
class InvalidItem : public BaseException {
    public:
        InvalidItem() {};
        void print() override;
};

// throwed when one tries to trade with same item
class SameItem : public BaseException {
    public:
        SameItem() {};
        void print() override;
};

// throwed when one tries to trade with himself
class TradeSelf : public BaseException {
    public:
        TradeSelf() {};
        void print() override;
};

// throwed when the trade-with player says "No" in order to decline this trade
class DeclineTrade : public BaseException {
    private:
        std::string tradeWith;
    public:
        DeclineTrade(std::string);
        void print() override;
};

// throwed when the ****loaded dice**** roll is beyond [2,12]
class DiceException : public BaseException {
    private:
        int rollNumber;
    public:
        DiceException(int);
        void print() override;
};

class RollInvalidNum : public BaseException {
    public:
        RollInvalidNum() {};
        void print() override;
};

// throwed when there has already a geese on a tile, the current player tries to put the geese on the same tile again.
//   ******   also this exception is throwed when user input an unsigned int but outside of [0,18]   ******
class GeeseCannotMove : public BaseException {
    public:
        GeeseCannotMove() {};
        void print() override;
};

class GeeseInvalidPos : public BaseException {
    public:
        GeeseInvalidPos() {};
        void print() override;
};

/* throwed when the geese cannot steal the resource:
    A.	There is no residence on the tile that the geese on.
    B.	All other players that have residence in that tile has no resource to steal from.
    C.	There are only the current player’s residence on that tile, thus cannot steal his own resource. */

class GeeseCannotSteal : public BaseException {
    private:
        std::string currBuilder;
    public:
        GeeseCannotSteal(std::string);  // customized constructor
        void print() override;
};

class FormatIncorrect : public BaseException {
    private:
        std::string fileName;
    public:
        FormatIncorrect(std::string);
        void print() override;
};

class UnableOpen : public BaseException {
    private:
        std::string fileName;
    public:
        UnableOpen(std::string);
        void print() override;
};

class LoadingWrong : public BaseException {
    public:
        LoadingWrong() { };
        void print() override;
};

class LoadMissFile : public BaseException {
    public:
        LoadMissFile() {};
        void print() override;
};

class BoardMissFile : public BaseException {
    public:
        BoardMissFile() {};
        void print() override;
};

class SeedMissNumber : public BaseException {
    public:
        SeedMissNumber() {};
        void print() override;
};

class RandomBoardMiss : public BaseException {
    private:
        std::string argument;
    public:
        RandomBoardMiss(std::string);
        void print() override;
};

class CanNotSteal : public BaseException {
    public:
        CanNotSteal() {};
        void print() override;
};

class CannotUseMarket : public BaseException {
    private:
        std::string sell;
    public:
        CannotUseMarket(std::string s);
        void print() override;
};

class BuySameResource : public BaseException {
    public:
        BuySameResource() {};
        void print() override;
};

class AlreadySpecify : public BaseException {
    private:
        std::string type;
    public:
        AlreadySpecify(std::string);
        void print() override;
};

class BoardAlreadySpecify : public BaseException {
    private:
        std::string type;
    public:
        BoardAlreadySpecify(std::string);
        void print() override;
};

class LoadAlreadySpecify : public BaseException {
    private:
        std::string type;
    public:
        LoadAlreadySpecify(std::string);
        void print() override;
};

#endif
