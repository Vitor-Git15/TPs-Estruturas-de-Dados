#include "QuickSort.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

QuickSort::QuickSort(ListWords *List,
                     int Median,
                     int MaxTamPartition,
                     Order *LexOrder)
// Descrição: construtor do QuickSort com parâmetros, ordena a lista de acordo
//            com a ordem lexicográfica passada
// Entrada: lista a ser ordenada, quantidade de valores para cálculo da mediana,
//          tamanho máximo da partição para ordenar a lista com algoritmo simples
//          (Selection Sort) e a ordem lexicográfica estabelecida 
// Saída: -
{
  OrderList(List, List->First, List->Last, Median, MaxTamPartition, LexOrder);
}
void QuickSort::OrderList(ListWords *List,
                          Word* &Left,
                          Word* &Right,
                          int elements,
                          int MaxTamPartition,
                          Order *LexOrder)
// Descrição: responsável por fazer a ordenação da lista
// Entrada: lista, elemento a esquerda da lista, elemento a direita da lista, quantidade
//          de valores para o cálculo da mediana, tamanho máximo da partição para ordenar
//          com algoritmo simples e a ordem lexicográfica estabelecida
// Saída: -
{
  // inicialização dos iteratores
  Word* i = nullptr;
  Word* j = nullptr;
  
  Pointers P;
  // separa a lista com os elementos menor que o pivô a esquerda e maiores a direita do pivô
  P = Partition(List, Left, Right, i, j, elements, LexOrder);

  i = P.i;
  j = P.j;

  //ordena a partição a esquerda do vetor caso necessário
  if (j == nullptr);
  else if((j->iD - Left->iD + 1 > 0) && (j->iD - Left->iD + 1 <= MaxTamPartition)){
    SelectionSort SS;
    SS.OrderList(List, Left, j, LexOrder);
  }
  else if (Left->iD < j->iD){
    OrderList(List, Left, j, DEFAULTMEDIAN, MaxTamPartition, LexOrder);
  }

  //ordena a partição a direita do vetor caso necessário
  if (i == nullptr);
  else if ((Right->iD - i->iD + 1 > 0) && (Right->iD - i->iD + 1 <= MaxTamPartition)){
    SelectionSort SS;
    SS.OrderList(List, i, Right, LexOrder);
  }
  else if (i->iD < Right->iD){
    OrderList(List, i, Right, DEFAULTMEDIAN, MaxTamPartition, LexOrder);
  }
}
Word *QuickSort::getPivot(ListWords *List,
                          Word *Left,
                          Word *Right,
                          int elements,
                          Order *LexOrder)
// Descrição: retorna a mediana(pivô) da lista passada
// Entrada: lista, elemento a esquerda da lista, elemento a direita da lista, quantidade
//          de valores para o cálculo da mediana e a ordem lexicográfica estabelecida
// Saída: mediana da partição passada(pivô)
{
  erroAssert(Left->iD < Right->iD, "Referência aos extremos da lista é inválida");

  // verifica se a quantidade de valores para cálculo da mediana é válido, caso contrário
  // é setado o valor default = 1
  avisoAssert(List->total >= elements, "A quantidade de valores para cálculo da mediana é muito grande");
  if(List->total < elements)
    elements = DEFAULTMEDIAN;

  // caso a quantidade de valores para cálculo da médiana seja menor ou igual a 1
  if (elements <= DEFAULTMEDIAN)
    return Left;
  else if(elements > List->_words)
    elements = List->_words;
  // obtem um ponteiro para o final da partição de acordo com a quantidade de valores para
  // o cálculo da mediana.
  Word *j;
  j = Left;
  for (int i = 0; i < elements; i++){
    j = j->next;
  }

  // ordena a partição passada com um algoritmo simples (Selection Sort)
  SelectionSort S;
  S.OrderList(List, Left, j, LexOrder);

  // obtem um ponteiro para a mediana da partição
  j = Left;
  for (int word = 0; word < elements / 2; word++){
    j = j->next;
  }

  return j;
}
Pointers QuickSort::Partition(ListWords *List,
                          Word* &Left,
                          Word* &Right,
                          Word* &i,
                          Word* &j,
                          int elements,
                          Order *LexOrder)
// Descrição: ordena a partição passada pelo método QuickSort
// Entrada: lista, referência ao elemento da esquerda, referência ao elemento da direita,
//          referência aos iteratores da lista, quantidade de valores para cálculo da mediana
//          e a ordem lexicográfica estabelecida
// Saída: struct com os ponteiros atualizados dos iteratores após sua passagem pela função
{
  Word *pivot;
  pivot = new Word();
  
  // obtem o pivô da partição
  pivot = getPivot(List, Left, Right, elements, LexOrder);

  //inicializa os iteratores
  i = Left;
  j = Right;

  do{
    // encontra o elemento a esquerda do pivô com valor maior que ele
    while(LexOrder->strcmp(pivot->_word->word, i->_word->word) > 0) i = i->next;
    // encontra o elemento a direita do pivô com valor menor que ele
    while(LexOrder->strcmp(pivot->_word->word, j->_word->word) < 0) j = j->previous;

    if ((i != nullptr) && (j != nullptr) && (i->iD <= j->iD)){
      // caso o pivô vá sofrer alteração o ponteiro vai permanecer apontando para o seu valor
      if (pivot == i)
        pivot = j;
      else if (pivot == j)
        pivot = i;

      // se os iteratores apontarem para elementos diferentes eles são permutados
      if (i != j)
        List->swap(i, j);

      i = i->next;
      j = j->previous;
    }

  } while (((i != nullptr) && (j != nullptr)) && (i->iD <= j->iD));
  // struct com os iteratores atualizados na função
  Pointers P;
  P.i = i;
  P.j = j;
  return P;
}
