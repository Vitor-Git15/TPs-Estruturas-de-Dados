#ifndef SELECT
#define SELECT

#include "WordsList.hpp"
#include "LexOrder.hpp"

#define DEFAULTMEDIAN 1

class SelectionSort{
  public:
    SelectionSort();
    SelectionSort(ListWords* List,
                  Order* LexOrder);
    void OrderList(ListWords* List,
                   Word* Left,
                   Word* Right,
                   Order* LexOrder);
};

#endif