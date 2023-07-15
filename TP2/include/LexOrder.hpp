#ifndef ORDER
#define ORDER

#include <string>

#define LETTERS 26

#define MIN_LOWER 97
#define MAX_LOWER 122

// classe responsável por ceder a ordem lexicográfica de palavras
class Order{
  public:
    
    Order();

    void newOrder(std::string LexOrder);
    
    int convert(char &C);
    int strcmp(std::string S1, std::string S2);

    int alphabet[LETTERS];
};

#endif