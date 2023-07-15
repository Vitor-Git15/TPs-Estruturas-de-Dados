#include "HashTable.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#include <iostream>
#include <fstream>

Hash::Hash()
// Descrição: construtor da classe Hash, define uma tabela nula
// Entrada: -
// Saída: -
{
  HashTable = nullptr;
}
Hash::Hash(int size){
  this->Size = size;
  HashTable = (BinaryTree*) malloc (Size * sizeof (BinaryTree));
  for(int i = 0; i < Size; i++){
    ESCREVEMEMLOG((long int)(&(HashTable[i])),sizeof(int),0);
  }
}
Hash::~Hash()
// Descrição: destrutor da classe Hash
// Entrada: -
// Saída: -
{
  delete HashTable;
} 

void Hash::Insert(int Dest,
                  int ID,
                  std::string &message,
                  int words,
                  std::ofstream &FileOut)
// Descrição: insere um e-mail na partição determinada
// Entrada: código da caixa de entrada, ID da mensagem, mensagem, quantidade de
//          palavras e arquivo de saída
// Saída: -
{
  HashTable[Dest%Size].Insert(message, ID, Dest);
  FileOut << "OK: MENSAGEM " << ID << " PARA " << Dest << " ARMAZENADA EM " << Dest%Size;
  FileOut << std::endl;
}
void Hash::Search(int InBox,
                  int ID,
                  std::ofstream &FileOut)
// Descrição: método de pesquisa na tabela Hash
// Entrada: código da caixa de entrada, ID da mensagem e arquivo de saída
// Saída: -
{
  FileOut << "CONSULTA " << InBox << " " << ID << ": ";
  HashTable[InBox%Size].Search(ID, InBox, FileOut);
}
void Hash::Erase(int InBox,
                  int ID,
                  std::ofstream &FileOut)
// Descrição: método que elimina um determinado e-mail
// Entrada: código da caixa de entrada, ID da mensagem e arquivo de saída
// Saída: -
{
  HashTable[InBox%Size].Erase(ID, InBox, FileOut);
}
void Hash::AccessHash()
// Descrição: faz o acesso aos elementos da tabela Hash sequencialmente a
//            fim de realizar um mapeamento dos endereços de memória
// Entrada: -
// Saída: -
{
  for(int i = 0; i < Size; i ++){
    LEMEMLOG((long int)(&(HashTable[i])),sizeof(int),0);
    HashTable[i].AccessTree(HashTable[i].root);
  }
}
