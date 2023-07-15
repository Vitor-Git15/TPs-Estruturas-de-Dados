#include "LineProcessor.hpp"
#include "msgassert.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <fstream>

bool LineProcessor::isPoint(char &c)
// Descrição: verifica se o caractere passado é um ponto
// Entrada: caractere
// Saída: true caso seja ponto e false caso contrário
{
  // pontos que devem ser eliminados do final das palavras 
  int Points[] = {',','.','!','?',':',';','_'};

  // verifica se o caractere passado é um dos pontos -> {',','.','!','?',':',';','_'}
  for (int i = 0; i < 7; i++){
    
    if(c == Points[i]){
      return true;
    }
  }

  return false;
}

void LineProcessor::lowerTransformer(std::string &word)
// Descrição: responsável por padronizar todas as palavras para sua versão em minúsculo
// Entrada: palavra a ser padronizada
// Saída: -
{
  
  for(unsigned int i = 0; i < word.size(); i++){
    // caso a letra esteja no formato maiúculo ela é passada para o minúsculo
    if(( word[i] >= MIN_UPPER ) && ( word[i] <= MAX_UPPER )){
      word[i] += TO_LOWER; 
    }
  }
}

void LineProcessor::getLexOrder(std::string &string)
// Descrição: recebe o texto de definição da ordem lexicográfica e a padroniza
// Entrada: ordem lexicográfica não padronizada
// Saída: -
{

  std::stringstream stream(string);
  char letter;

  std::string alphabet = ""; 

  bool UpperFlag = false;

  while(stream >> letter){

    if(letter >= MIN_LOWER && letter <= MAX_LOWER){
      alphabet += letter;
    }

    else if(letter >= MIN_UPPER && letter <= MAX_UPPER){
      alphabet += letter;
      UpperFlag = true;
    }
  }
  // caso tenha letra maiúscula o texto com a ordem lexicográfica é passada pra sua versão em
  // minúsculo.
  if(UpperFlag)
    lowerTransformer(alphabet);

  string = alphabet;
}
void LineProcessor::getWords(const std::string &str,
                             ListWords* List)
// Descrição: enfileira as palavras passadas no texto na classe ListWords
// Entrada: linha do texto a ser analisada e lista onde serão enfileirados
// Saída: -
{

  std::stringstream stream(str);
  std::string word;


  // verifica cada palavra do texto passado
  while(stream >> word){

    for(int i = word.size() - 1; i > 0; i--){
      
      // caso o último elemento seja um ponto ele é removido da palavra
      if(isPoint(word[i])){
        word.erase(word.size() - 1);
      }
      
      // caso o último elemento não seja não há necessidade de remoções
      else{
        break;
      }
    }

    lowerTransformer(word);
    List->AddNewWord(word);
  }
}
void LineProcessor::getTexts(std::ifstream &FileIn,
                             Order* LexOrder,
                             ListWords* List)
// Descrição: responsável pela análise do texto contida no arquivo de entrada e obtenção 
//            de todos os parâmetros
// Entrada: arquivo de entrada, ponteiro para classe que define a ordem lexicográfica e
//          a lista onde as palavras serão enfileirada
// Saída: -
{
  std::string LineText;

  while(getline(FileIn, LineText)){

    std::stringstream stream(LineText);
    std::string identifier;

    stream >> identifier;

    // texto a ser análisado
    if(identifier == "#TEXTO"){
      
      std::string Line;
      while(getline(FileIn, Line)){
        if(Line == "#ORDEM"){
          identifier = "#ORDEM";
          break;
        }
        else{
          getWords(Line, List);
        }
      }
    }

    // definição de uma nova ordem
    else if(identifier == "#ORDEM"){

      std::string alphabet;
      getline(FileIn, alphabet);

      getLexOrder(alphabet);

      LexOrder->newOrder(alphabet);
    }
  }  
}
