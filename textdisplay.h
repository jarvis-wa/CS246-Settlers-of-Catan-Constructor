#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"
#include "vertex.h"
#include "tile.h"
#include <vector>
#include "subject.h"
#include "edge.h"
#include <string>

class TextDisplay: public Observer {
    private: // 先全是public，test完改回private
        std::vector<std::string> vertex;
        std::vector<std::string> edge;
        std::vector<std::string> tileIndex;
        std::vector<std::pair<int, std::string>> tileInfo;   // first is the tile source, second is the tile value
        int geesePos = -1;       // record the Geese position
    public:
        TextDisplay(std::vector<std::pair<int, int>>);
        ~TextDisplay() { };
        void notify(Subject& whoNotified) noexcept override;      // td is the observer of vertex, edge and tile
       // void changeGeesePos(int);       // mutate geesePos
        void print() noexcept;
        std::string resourcePrint(int) noexcept;
        std::string valuePrintRow(std::string) noexcept;
        void changeGeesePos(int) noexcept;
};

#endif
