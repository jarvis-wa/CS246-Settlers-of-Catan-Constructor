#include "textdisplay.h"
#include <sstream>

TextDisplay::TextDisplay(std::vector<std::pair<int, int>> infoTile) {
    std::vector<std::string> vertex;
    std::vector<std::string> edge;
    std::vector<std::string> tileIndex;
    std::vector<std::pair<int, std::string>> infoOfTile;
    for (int i = 0; i < 54; i++) {  // vertex: (" 0"," 1", ..., "53")
        if (i < 10) {
            vertex.emplace_back(" " + std::to_string(i));
        } else {
            vertex.emplace_back(std::to_string(i));
        }
    }
    for (int i = 0; i < 72; i++) {  // edge: (" 0", " 1", ..., "71")
        if (i < 10) {
            edge.emplace_back(" " + std::to_string(i));
        } else {
            edge.emplace_back(std::to_string(i));
        }
    }
    for (int i = 0; i < 19; i++) {   // tileIndex: (" 0", " 1", ..., "18")
        if (i < 10) {
            tileIndex.emplace_back(" " + std::to_string(i));
        } else {
            tileIndex.emplace_back(std::to_string(i));
        }
    }
    for (auto& n : infoTile) { // InfoTile: (<0,3>,<1,10>,....)
        if (n.second < 10) {
            if (n.second == 7) {
                infoOfTile.emplace_back(std::make_pair(n.first, "  "));  // if the source is a PARK, then we just make the corresponding value "  ";
                                                                    // since we don't need to print the value of a tile with PARK
            } else {
            infoOfTile.emplace_back(std::make_pair(n.first, " " + std::to_string(n.second)));
            }
        } else {
            infoOfTile.emplace_back(std::make_pair(n.first , std::to_string(n.second)));
        }
    }
    this->vertex = vertex;
    this->edge = edge;
    this->tileIndex = tileIndex;
    this->tileInfo = infoOfTile;    // tileInfo: (<0," 3">,<1,"10">,..<5, "  ">..)
}
// TextDisplay::~TextDisplay() { };

void TextDisplay::notify(Subject& whoNotified) noexcept {
   //  std::cout << "enter notify" << std::endl;
    int x;
    int currPos = whoNotified.returnPos();
    if (whoNotified.returnType() == "vertex") {     // *****td is notified by vertex******
        int playerNum = whoNotified.getOwnerInfo().at(0).get()->returnWho();
        std::string& currContent = this->vertex.at(currPos);
        std::istringstream iss{ currContent };
        iss >> x;
        if ( iss.fail() ) {        // if the transformation from string to int fails, then it must be occupied
                                    // thus we need to improve the current house
            if (currContent[1] == 'B') {        //  basement ==> house
                currContent.replace(1, 1, "H");
            } else if (currContent[1] == 'H') {     // house ==> tower
                currContent.replace(1, 1, "T");
            }
        } else {    // successfully transform string to int => means no owner has house on the vertex
            this->vertex.at(currPos) = changePlayerName(playerNum).substr(0,1) + 'B';   // initially it's a basement(B)
        }
    } else if (whoNotified.returnType() == "edge") {    // notified by an edge
       // std::cout << "enter edge if else" << std::endl;
        int playerNum = whoNotified.getOwnerInfo().at(0).get()->returnWho();
        std::string& currEdge = this->edge.at(currPos);
        currEdge = changePlayerName(playerNum).substr(0,1) + 'R';
    } else {        // notified by a tile
      //  std::cout << "enter tile notify.........." << std::endl;
        this->geesePos = currPos;
    }
}

std::string TextDisplay::resourcePrint(int sourceType) noexcept {
    std::string s;
    if (sourceType == 0) {
        s = "  BRICK  ";
    } else if (sourceType == 1) {
        s = " ENERGY  ";
    } else if (sourceType == 2) {
        s = "  GLASS  ";
    } else if (sourceType == 3) {
        s = "  HEAT   ";
    } else if (sourceType == 4) {
        s = "  WIFI   ";
    } else {
        s = "  PARK   ";
    }
    return s;
}

std::string TextDisplay::valuePrintRow(std::string strValue) noexcept {
    std::string s = "  " + strValue + "  ";
    // unsigned int length = strValue;
    // std::string valueStr = std::to_string(value);
   // if ((row - 1) % 4 == 0) {     // 5 9 13 17 21 25 29 33 37 (row)
      //  s = "  " + strValue + "  ";
   // } else {
   //     s = "   " + strValue + "   ";
   // }
    return s; 
}

void TextDisplay::print() noexcept {
    //int rowNum = 1;
    int geesePos = this->geesePos;
    //  *******1st row**********
    std::cout << "                    |" << this->vertex.at(0) << "|--" << this->edge.at(0) << "--|" << this->vertex.at(1) << "|" << std::endl; 
    //rowNum++;
    //  *******2nd row**********
    std::cout << "                      |         |" << std::endl;
    //rowNum++;
    //  *******3rd row**********
    std::cout << "                     " << this->edge.at(1) << "   " << this->tileIndex.at(0) << "   " << this->edge.at(2) << std::endl;
   // rowNum++;
    //  *******4th row*********
    std::cout << "                      |" << resourcePrint(this->tileInfo.at(0).first) << "|" << std::endl;
    //rowNum++;
    //  *******5th row*********
    std::cout << "          |" << this->vertex.at(2) << "|--" << this->edge.at(3) << "--|" << this->vertex.at(3) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(0).second) << "|" << this->vertex.at(4) << "|--" << this->edge.at(4) << "--|" << this->vertex.at(5) << "|" << std::endl;
    //  *******6th row**********
    if (geesePos == 0) {
        std::cout << "            |         |  GEESE  |         |" << std::endl;
    } else {
        std::cout << "            |         |         |         |" << std::endl;
    }
    //  *******7th row**********
    std::cout << "           " << this->edge.at(5) << "   " << this->tileIndex.at(1) << "   " << this->edge.at(6) << "        " << this->edge.at(7) << "   " << this->tileIndex.at(2) << "   " << this->edge.at(8) << std::endl;
    //  *******8th row**********
    std::cout << "            |" << resourcePrint(this->tileInfo.at(1).first) << "|         |" << resourcePrint(this->tileInfo.at(2).first) << "|" << std::endl;
    //  *******9th row**********
    std::cout << "|" << this->vertex.at(6) << "|--" << this->edge.at(9) << "--|" << this->vertex.at(7) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(1).second) << "|" << this->vertex.at(8) << "|" << "--" << this->edge.at(10) << "--|" << this->vertex.at(9) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(2).second) << "|" << this->vertex.at(10) << "|" << "--" << this->edge.at(11) << "--|" << this->vertex.at(11) << "|" << std::endl;
    //  *******10th row*********
    if (geesePos == 1) {
        std::cout << "  |         |  GEESE  |         |         |         |" << std::endl;
    } else if (geesePos == 2) {
        std::cout << "  |         |         |         |  GEESE  |         |" << std::endl;
    } else {
        std::cout << "  |         |         |         |         |         |" << std::endl;
    }
    //  ****11th row***********
    std::cout << " " << this->edge.at(12) << "   " << this->tileIndex.at(3) << "   " << this->edge.at(13) << "        " << this->edge.at(14) << "   " << this->tileIndex.at(4) << "   " << this->edge.at(15);
    std::cout << "        " << this->edge.at(16) << "   " << this->tileIndex.at(5) << "   " << this->edge.at(17) << std::endl;
    //  *****12th row*********
    std::cout << "  |" << resourcePrint(this->tileInfo.at(3).first) << "|         |" << resourcePrint(this->tileInfo.at(4).first) << "|         |" << resourcePrint(this->tileInfo.at(5).first) << "|" << std::endl;
    //  *****13th row ********
    std::cout << "|" << this->vertex.at(12) << "|" << valuePrintRow(this->tileInfo.at(3).second) << "|" << this->vertex.at(13) << "|--" << this->edge.at(18) << "--|" << this->vertex.at(14) << "|" << valuePrintRow(this->tileInfo.at(4).second);
    std::cout << "|" << this->vertex.at(15) << "|" << "--" << this->edge.at(19) << "--|" << this->vertex.at(16) << "|" << valuePrintRow(this->tileInfo.at(5).second) << "|" << this->vertex.at(17) << "|" << std::endl;
    //  *****14th row*********
    if (geesePos == 3) {
        std::cout << "  |  GEESE  |         |         |         |         |" << std::endl;
    } else if (geesePos == 4) {
        std::cout << "  |         |         |  GEESE  |         |         |" << std::endl;
    } else if (geesePos == 5) {
        std::cout << "  |         |         |         |         |  GEESE  |" << std::endl;
    } else {
        std::cout << "  |         |         |         |         |         |" << std::endl;
    }
    //  *****15th row******
    std::cout << " " << this->edge.at(20) << "        " << this->edge.at(21) << "   " << this->tileIndex.at(6) << "   " << this->edge.at(22);
    std::cout << "        " << this->edge.at(23) << "   " << this->tileIndex.at(7) << "   " << this->edge.at(24) << "        " << this->edge.at(25) << std::endl;
    //  *****16th row*******
    std::cout << "  |         |" << resourcePrint(this->tileInfo.at(6).first) << "|         |" << resourcePrint(this->tileInfo.at(7).first) << "|         |" << std::endl;
    //  ******17th row******
    std::cout << "|" << this->vertex.at(18) << "|--" << this->edge.at(26) << "--|" << this->vertex.at(19) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(6).second) << "|" << this->vertex.at(20) << "|" << "--" << this->edge.at(27) << "--|" << this->vertex.at(21) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(7).second) << "|" << this->vertex.at(22) << "|" << "--" << this->edge.at(28) << "--|" << this->vertex.at(23) << "|" << std::endl;
    //  ******18th row*******
    if (geesePos == 6) {
        std::cout << "  |         |  GEESE  |         |         |         |" << std::endl;
    } else if (geesePos == 7) {
        std::cout << "  |         |         |         |  GEESE  |         |" << std::endl;
    } else {
        std::cout << "  |         |         |         |         |         |" << std::endl;
    }
    //   ******19th row********
    std::cout << " " << this->edge.at(29) << "   " << this->tileIndex.at(8) << "   " << this->edge.at(30) << "        " << this->edge.at(31) << "   " << this->tileIndex.at(9) << "   " << this->edge.at(32);
    std::cout << "        " << this->edge.at(33) << "   " << this->tileIndex.at(10) << "   " << this->edge.at(34) << std::endl;
    //    *****20th row********
    std::cout << "  |" << resourcePrint(this->tileInfo.at(8).first) << "|         |" << resourcePrint(this->tileInfo.at(9).first) << "|         |" << resourcePrint(this->tileInfo.at(10).first) << "|" << std::endl;
    //    *****21th row********
    std::cout << "|" << this->vertex.at(24) << "|" << valuePrintRow(this->tileInfo.at(8).second) << "|" << this->vertex.at(25) << "|--" << this->edge.at(35) << "--|" << this->vertex.at(26) << "|"  << valuePrintRow(this->tileInfo.at(9).second);
    std::cout << "|" << this->vertex.at(27) << "|" << "--" << this->edge.at(36) << "--|" << this->vertex.at(28) << "|" << valuePrintRow(this->tileInfo.at(10).second) << "|" << this->vertex.at(29) << "|" << std::endl;
    //    *****22th row********
    if (geesePos == 8) {
        std::cout << "  |  GEESE  |         |         |         |         |" << std::endl;
    } else if (geesePos == 9) {
        std::cout << "  |         |         |  GEESE  |         |         |" << std::endl;
    } else if (geesePos == 10) {
        std::cout << "  |         |         |         |         |  GEESE  |" << std::endl;
    } else {
        std::cout << "  |         |         |         |         |         |" << std::endl;
    }
    //    ****23th row*******
    std::cout << " " << this->edge.at(37) << "        " << this->edge.at(38) << "   " << this->tileIndex.at(11) << "   " << this->edge.at(39);
    std::cout << "        " << this->edge.at(40) << "   " << this->tileIndex.at(12) << "   " << this->edge.at(41) << "        " << this->edge.at(42) << std::endl;
    //    *****24th row*******
    std::cout << "  |         |" << resourcePrint(this->tileInfo.at(11).first) << "|         |" << resourcePrint(this->tileInfo.at(12).first) << "|         |" << std::endl;
    //    ****25th row********
    std::cout << "|" << this->vertex.at(30) << "|--" << this->edge.at(43) << "--|" << this->vertex.at(31) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(11).second) << "|" << this->vertex.at(32) << "|" << "--" << this->edge.at(44) << "--|" << this->vertex.at(33) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(12).second) << "|" << this->vertex.at(34) << "|" << "--" << this->edge.at(45) << "--|" << this->vertex.at(35) << "|" << std::endl;
    //      ****26th row******
    if (geesePos == 11) {
        std::cout << "  |         |  GEESE  |         |         |         |" << std::endl;
    } else if (geesePos == 12) {
        std::cout << "  |         |         |         |  GEESE  |         |" << std::endl;
    } else {
        std::cout << "  |         |         |         |         |         |" << std::endl;
    }
    //       *****27th row******
    std::cout << " " << this->edge.at(46) << "   " << this->tileIndex.at(13) << "   " << this->edge.at(47) << "        " << this->edge.at(48) << "   " << this->tileIndex.at(14) << "   " << this->edge.at(49);
    std::cout << "        " << this->edge.at(50) << "   " << this->tileIndex.at(15) << "   " << this->edge.at(51) << std::endl;
    //      ******28th row******
    std::cout << "  |" << resourcePrint(this->tileInfo.at(13).first) << "|         |" << resourcePrint(this->tileInfo.at(14).first) << "|         |" << resourcePrint(this->tileInfo.at(15).first) << "|" << std::endl;
    //      ******29th row*******
    std::cout << "|" << this->vertex.at(36) << "|" << valuePrintRow(this->tileInfo.at(13).second) << "|" << this->vertex.at(37) << "|--" << this->edge.at(52) << "--|" << this->vertex.at(38) << "|" << valuePrintRow(this->tileInfo.at(14).second);
    std::cout << "|" << this->vertex.at(39) << "|" << "--" << this->edge.at(53) << "--|" << this->vertex.at(40) << "|" << valuePrintRow(this->tileInfo.at(15).second) << "|" << this->vertex.at(41) << "|" << std::endl;
    //      ******30th row********
    if (geesePos == 13) {
        std::cout << "  |  GEESE  |         |         |         |         |" << std::endl;
    } else if (geesePos == 14) {
        std::cout << "  |         |         |  GEESE  |         |         |" << std::endl;
    } else if (geesePos == 15) {
        std::cout << "  |         |         |         |         |  GEESE  |" << std::endl;
    } else {
        std::cout << "  |         |         |         |         |         |" << std::endl;
    }
    //    *********31th row********
    std::cout << " " << this->edge.at(54) << "        " << this->edge.at(55) << "   " << this->tileIndex.at(16) << "   " << this->edge.at(56);
    std::cout << "        " << this->edge.at(57) << "   " << this->tileIndex.at(17) << "   " << this->edge.at(58) << "        " << this->edge.at(59) << std::endl;
    //    ******32th row******
    std::cout << "  |         |" << resourcePrint(this->tileInfo.at(16).first) << "|         |" << resourcePrint(this->tileInfo.at(17).first) << "|         |" << std::endl;
    //    ******33th row*****
    std::cout << "|" << this->vertex.at(42) << "|--" << this->edge.at(60) << "--|" << this->vertex.at(43) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(16).second) << "|" << this->vertex.at(44) << "|" << "--" << this->edge.at(61) << "--|" << this->vertex.at(45) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(17).second) << "|" << this->vertex.at(46) << "|" << "--" << this->edge.at(62) << "--|" << this->vertex.at(47) << "|" << std::endl;
    //     ****34th row******
    if (geesePos == 16) {
        std::cout << "            |  GEESE  |         |         |" << std::endl;
    } else if (geesePos == 17) {
        std::cout << "            |         |         |  GEESE  |" << std::endl;
    } else {
        std::cout << "            |         |         |         |" << std::endl;
    }
    //    ****35th row********
    std::cout << "           " << this->edge.at(63) << "        " << this->edge.at(64) << "   " << this->tileIndex.at(18) << "   " << this->edge.at(65) << "        " << this->edge.at(66) << std::endl;
    //   ******36th row*******
    std::cout << "            |         |" << resourcePrint(this->tileInfo.at(18).first) << "|         |" << std::endl;
    //   *****37th row*******
    std::cout << "          |" << this->vertex.at(48) << "|--" << this->edge.at(67) << "--|" << this->vertex.at(49) << "|";
    std::cout << valuePrintRow(this->tileInfo.at(18).second) << "|" << this->vertex.at(50) << "|--" << this->edge.at(68) << "--|" << this->vertex.at(51) << "|" << std::endl;
    //   ****38th row*******
    if (geesePos == 18) {
        std::cout << "                      |  GEESE  |" << std::endl;
    } else {
        std::cout << "                      |         |" << std::endl;
    }
    //     ****39th row*****
    std::cout << "                     " << this->edge.at(69) << "        " << this->edge.at(70) << std::endl;
    //     ***40th row*****
    std::cout << "                      |         |" << std::endl;
    //    ****LAST LINE******
    std::cout << "                    |" << this->vertex.at(52) << "|--" << this->edge.at(71) << "--|" << this->vertex.at(53) << "|" << std::endl;
}

void TextDisplay::changeGeesePos(int pos) noexcept{
    this->geesePos = pos;
}
