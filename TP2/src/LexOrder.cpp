#include "LexOrder.hpp"
#include <iostream>

Order::Order()
// Descrição: construtor da classe Order, define, por padrão, a ordem alfabética
// Entrada: -
// Saída: -
{
  for (int letter = 0; letter < LETTERS; letter++){
    alphabet[letter] = letter;
  }  
}

void Order::newOrder(std::string LexOrder)
// Descrição: define a nova ordem lexicográfica
// Entrada: string com a nova ordem lexicográfica no formato "(caractere1)(caractere2)...(caractere26)"
// Saida: -
{

  for (int letter = 0; letter < LETTERS; letter++){

    char c = LexOrder[letter];
    alphabet[c - MIN_LOWER] = letter;
  }
}

int Order::convert(char &C)
// Descrição: converte o caractere passado para seu novo valor de acordo com a ordem lexicográfica estabelecida
// Entrada: caractere
// Saída: código de acordo com o novo padrão
{
  if(C >= MIN_LOWER && C <= MAX_LOWER){
    // retorna o novo código do caractere de acordo com a nova ordem
    return MIN_LOWER + alphabet[C - MIN_LOWER];
  } 

  return C;
}

int Order::strcmp(std::string S1, 
                  std::string S2)
// Descrição: recebe duas strings e as compara de acordo com a ordem lexicográfica estabelecida
// Entrada: strings a serem comparadas
// Saída: Negativa [S1 < S2]; Positiva [S1 > S2]; Nula [S1 = S2]
{

  int MaxSize;
  // atribui a variável o tamanho da maior string
  MaxSize = (S1.size() >= S2.size()) ? S1.size() : S2.size();

  for(int letter = 0; letter < MaxSize; letter++){

    // se o caractere diferirem ou acabar as letras de uma das strings quebra-se o loop
    if(S1[letter] != S2[letter]){

      return convert(S1[letter]) - convert(S2[letter]);
    }
  }

  // se todos os caracteres são iguais, mesmo percorrendo a maior palavra, as strings são iguais
  return 0;
}