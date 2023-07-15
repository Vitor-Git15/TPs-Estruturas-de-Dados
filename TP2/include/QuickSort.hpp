#ifndef SORT
#define SORT
 
#include "WordsList.hpp"
#include "LexOrder.hpp"
#include "SelectionSort.hpp"
 
#define DEFAULTMEDIAN 1

struct Pointers{
  Word* i;
  Word* j;
};

class QuickSort{
 public:
   QuickSort();
   QuickSort(ListWords* List,
             int Median,
             int MaxTamPartition,
             Order* LexOrder);
   void OrderList(ListWords* List,
                  Word* &Left,
                  Word* &Right,
                  int elements,
                  int MaxTamPartition,
                  Order* LexOrder);
   Word* getPivot(ListWords* List,
                  Word* Left,
                  Word* Right,
                  int elements,
                  Order* LexOrder);
   Pointers Partition(ListWords* List,
                  Word* &Left,
                  Word* &Right,
                  Word* &i,
                  Word* &j,
                  int elements,
                  Order* LexOrder);
};

#endif