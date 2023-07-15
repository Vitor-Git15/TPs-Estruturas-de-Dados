#include "WordsList.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

/*------------------------------------------------------------------------------------------*/
/*                                   FUNÇÕES DA CLASSE WORD                                 */
/*------------------------------------------------------------------------------------------*/

Word::Word()
// Descrição: construtor padrão da classe Word
// Entrada: -
// Saída: -
{
  this->_word = nullptr;
  this->iD = -1;
  this->next = nullptr;
  this->previous = nullptr;
}

Word::Word(std::string &word,
           int qnt,
           int iD,
           Word* next,
           Word* previous)
// Descrição: construtor da classe Word
// Entrada: palavra inserida, ocorrecias no texto, proxima palavra, palavra anterior.
// Saída; -         
{
  this->_word = new words(word , qnt);
  this->iD = iD;
  this->next = next;
  this->previous = previous;
}

/*------------------------------------------------------------------------------------------*/
/*                                   FUNÇÕES DA CLASSE LIST                                 */
/*------------------------------------------------------------------------------------------*/

#include <iostream>

#define INTSWAP(x,y) (x+=y,y=x-y,x-=y)

ListWords::ListWords()
// Descrição: construtor padrão da classe ListWords
// Entrada: -
// Saída: -
{
  First = nullptr;
  Last = First;
  _words = 0;
  total = 0;
}
ListWords::~ListWords()
// Descrição: destrutor da classe ListWords
// Entrada: -
// Saída: -
{
  Word* clean, *w_aux;
  w_aux = this->First;
  
  while(w_aux != nullptr){
    clean = w_aux;
    w_aux = w_aux->next;
    delete clean;
  }
}
void ListWords::AddNewWord(std::string word)
// Descrição: adiciona palavra a fila, no final se não houver ocorrência, se houver é adionado 1
//            a Word já existente
// Entrada: palavra a ser adicionada
// Saida: -
{
  // se a fila ainda não foi inicializada
  if(First == nullptr){
    First = new Word(word, 1, _words, nullptr, nullptr);
    Last = First;
    _words++;
    total++;
    ESCREVEMEMLOG((long int)(&(First->_word)),sizeof(std::string),0);
  }
  else{
    Word* w_aux;
    w_aux = First;

    // verifica se a palavra sá esta na lista
    while(w_aux != nullptr){
      
      // caso a palavra esteja na lista
      if(w_aux->_word->word == word){
        w_aux->_word->qnt++;
        total++;
        return ;
      }

      w_aux = w_aux->next;
    }

    // insere a palavra no final da lista
    Last->next = new Word(word, 1, _words, nullptr, Last);
    Last = Last->next;
    _words++;
    total++;
    ESCREVEMEMLOG((long int)(&(Last->_word)),sizeof(std::string),0);
  }
}
void ListWords::swap(Word* &W1,
                     Word* &W2)
// Descrição: troca os dados dos elementos W1 e W2 da lista
// Entrada: ponteiro para os elementos W1 e W2 da lista
// Saída: -
{
  // caso algum dos elementos que vão ser trocados seja nulo a operação não é realizada
  avisoAssert(W1 != nullptr && W2 != nullptr, "Argumentos passados no swap são inválidos");
  if(W1 == nullptr || W2 == nullptr)
    return ;

  // troca a quantidade de palavras iguais de W1 e W2 da lista
  INTSWAP(W1->_word->qnt, W2->_word->qnt);

  // troca as palavras de W1 e W2
  std::string w_aux;
  w_aux = W1->_word->word; W1->_word->word = W2->_word->word; W2->_word->word = w_aux;
  LEMEMLOG((long int)(&(W1->_word)),sizeof(std::string),0);
  LEMEMLOG((long int)(&(W2->_word)),sizeof(std::string),0);
}
void ListWords::ListAccess()
// Descrição: Acessa os elementos da lista sequencialmente para fins de registro de acesso
// Entrada: -
// Saída: -
{
  Word* w_aux;
  w_aux = First;

  while(w_aux != nullptr){
    LEMEMLOG((long int)(&(w_aux->_word)),sizeof(std::string),0);
    w_aux = w_aux->next;
  }
}
void ListWords::Print(std::ofstream &FileOut)
// Descrição: insere as palavras e a quantidade de repetições dessa em um arquivo seguindo a
//            ordem lexicográfica estabelecida
// Entrada: referência ao arquivo de saída
// Saída: -
{
  Word* w_aux;
  w_aux = First;

  // insere a palavra e a quantidade de repetições dela no arquivo de saída
  while(w_aux != nullptr){
    FileOut << w_aux->_word->word << " " << w_aux->_word->qnt << std::endl;
    LEMEMLOG((long int)(&(w_aux->_word)),sizeof(std::string),0);
    w_aux = w_aux->next;
  }
  FileOut << "#FIM";
}