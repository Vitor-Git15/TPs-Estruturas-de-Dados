#include "LineProcessor.hpp"
#include "msgassert.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <fstream>

int LineProcessor::getHashSize(std::ifstream &FileIn)
// Descrição: responsável por obter o tamanho da tabela descrita no arquivo de entrada
// Entrada: arquivo de entrada
// Saída: valor da tabela Hash
{
  std::string HS;
  getline(FileIn, HS);

  return std::stoi(HS);
}
void LineProcessor::getTexts(std::ifstream &FileIn,
                             Hash* HashTable,
                             std::ofstream &FileOut)
// Descrição: responsável pela análise do texto contida no arquivo de entrada e obtenção 
//            de todos os parâmetros
// Entrada: arquivo de entrada, ponteiro para a tabela Hash e arquivo de saída
// Saída: -
{
  std::string LineText;

  while(getline(FileIn, LineText)){

    std::stringstream stream(LineText);
    std::string identifier;

    stream >> identifier;

    // obtem os dados do email a ser adicionado
    if(identifier == "ENTREGA"){

      int InBox, ID, Words;
      stream >> InBox >> ID >> Words;
      
      if((InBox < 0) || (ID < 0) || (Words < 0)){
        avisoAssert((InBox >= 0) && (ID >= 0) && (Words >= 0), "Parâmetro devem ser não negativos");
        continue;
      }

      std::string message = ""; 
      std::string m_aux = "";

      for(int i = 0; i < Words; i++){
        stream >> m_aux;

        message += m_aux;
        if(i != Words-1)
          message += ' ';
      }

      HashTable->Insert(InBox, ID, message, Words, FileOut);
    }

    // obtem os dados do email a ser procurado
    else if(identifier == "CONSULTA"){
      int InBox, ID;
      stream >> InBox >> ID;

      avisoAssert((InBox >= 0) && (ID >= 0), "Parâmetros devem ser não negativos");
      
      HashTable->Search(InBox, ID, FileOut);
    }

    // obter os dados do email a ser deletado
    else if(identifier == "APAGA"){
      int InBox, ID;
      stream >> InBox >> ID;
      avisoAssert((InBox >= 0) && (ID >= 0), "Parâmetros devem ser não negativos");

      HashTable->Erase(InBox, ID, FileOut);
    }
  }  
}
