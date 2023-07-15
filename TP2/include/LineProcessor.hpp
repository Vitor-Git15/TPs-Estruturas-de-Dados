#ifndef LINEPROCESSOR
#define LINEPROCESSOR

#include <string>
#include <fstream>

#include "LexOrder.hpp"
#include "WordsList.hpp"

#define MIN_LOWER 97
#define MAX_LOWER 122

#define TO_LOWER 32

#define MIN_UPPER 65
#define MAX_UPPER 90

class LineProcessor{
  public:
    bool isPoint(char &c);
    void lowerTransformer(std::string &word);
    void getLexOrder(std::string &string);
    void getWords(const std::string &str, ListWords* List);
    void getLexOrder(const std::string &LexOrder);
    void getTexts(std::ifstream &FileIn,
                  Order* LexOrder,
                  ListWords* List);
    
};

#endif