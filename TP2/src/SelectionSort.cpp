#include "SelectionSort.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

SelectionSort::SelectionSort(){}
SelectionSort::SelectionSort(ListWords* List,
                             Order* LexOrder)
// Descrição: construtor do SelectionSort com parâmetros, ordena a lista de acordo
//            com a ordem lexicográfica passada
// Entrada: lista e a ordem lexicográfica estabelecida
// Saída: -
{
  this->OrderList(List, List->First, List->Last, LexOrder);
}                             
void SelectionSort::OrderList(ListWords* List,
                              Word* Left,
                              Word* Right,
                              Order* LexOrder)
// Descrição: método de ordenação da lista de palavras por algoritmo simples (Selection Sort)
// Entrada: lista, elemento a esquerda, elemento a direita e a ordem lexicográfica estabelecida
// Saída: -
{
  Word* MinWord;
  
  // ordena a lista
  for(Word* i = Left; i != Right; i = i->next){

    if(i == nullptr)
      return ;

    MinWord = i;
    for(Word* j = i->next; j != Right->next ; j = j->next){
      
      if(j == nullptr)
        return ;
      //caso exista um elemento na partição menor do que o MinWord o MinWord passa a apontar para ele
      else if(LexOrder->strcmp(j->_word->word, MinWord->_word->word) < 0)
        MinWord = j;
    }
    // coloca o menor elemento no seu devido lugar caso ele não esteja
    if(i != MinWord){
      List->swap(i, MinWord);
    }
  }
}