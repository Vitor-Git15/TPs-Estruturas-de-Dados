#ifndef PROCESSOR
#define PROCESSOR

#include "HashTable.hpp"

class LineProcessor{
  public:
    LineProcessor(){}
    int getHashSize(std::ifstream &FileIn);
    void getTexts(std::ifstream &FileIn,
                  Hash* HashTable,
                  std::ofstream &FileOut);
};

#endif