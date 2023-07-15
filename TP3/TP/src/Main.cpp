#include "Email.hpp"
#include "BinaryTree.hpp"
#include "HashTable.hpp"
#include "LineProcessor.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>

// definição da struct no qual serão armazenadas as opções de entrada
struct opt{

  std::string FileOut = "out.txt";
  std::string FileIn = "in.txt"; 
  std::string FilePerf = "";

  bool MemReg = false;
};

std::ifstream OpenInFiles(opt* opt)
// Descrição: abre o arquivo de entrada e o retorna
// Entrada: struct com as opções de entrada
// Saída: arquivo de entrada aberto
{

  std::ifstream file(opt->FileIn);

  // caso não seja possível abrir o arquivo de entrada
  erroAssert(file.is_open(), "Erro na abertura do arquivo de entrada");

  return file;
}
std::ofstream OpenOutFiles(opt* opt)
// Descrição: abre o arquivo de saída e o retorna
// Entrada: struct com as opções de entrada
// Saída: arquivo de saída aberto
{
  std::ofstream file(opt->FileOut);

  // caso não seja possível abrir o arquivo de saída
  erroAssert(file.is_open(), "Erro na abertura do arquivo de entrada");

  return file;
}
void use()
// Descrição: printa na saída padrão as opções disponíveis
// Entrada: -
// Saída: -
{
  std::cout << "\n\t*-----------------------OPÇÕES-----------------------*\t" << std::endl;
  std::cout << "\t -[i|I] - Endereço arquivo de entrada\t" << std::endl;
  std::cout << "\t -[o|O] - Endereço arquivo de saída\t" << std::endl;
  std::cout << "\t -[p|P] - Endereço arquivo registro de desempenho\t" << std::endl;
  std::cout << "\t -[l|L] - Padrão de acesso e localidade\t" << std::endl;
  std::cout << "\t*-----------------------------------------------------*\t" << std::endl;
}
void ParseArgs(int argc, char **argv, opt* options)
// Descrição: obtem as informações passadas na chamada da função
// Entrada: argumentos passados na chamada da função
// Saída: -
{

  int option;

  while((option = getopt(argc, argv, "i:I:o:O:p:P:l:L")) != EOF){

    // arquivo de entrada com o texto a ser processado e a nova ordem lexicográfica 
    if(option == 'i' || option == 'I'){
      options->FileIn = optarg;
    }

    // endereço do arquivo de saída
    else if(option == 'o' || option == 'O'){
      options->FileOut = optarg;
    }

    // endereço do arquivo performace
    else if(option == 'p' || option == 'P'){
      options->FilePerf = optarg;
    }

    // padrão de acesso e localidade
    else if(option == 'l' || option == 'L'){
      options->MemReg = true;
    }

    // caso padrão
    else{
      use();
      exit(1);
    }
  }
}
int main(int argc,
         char **argv)
// Descrição: função principal do programa
// Entrada: argumentos passados na chama da função
// Saída: false caso não tenha erro e true caso tenha
{
  opt option;
  ParseArgs(argc, argv, &option);

  // inicia registro de acesso caso solicitado
  if(option.FilePerf != ""){
    char LogName[50];
    strcpy(LogName, option.FilePerf.c_str());
    iniciaMemLog(LogName);
  }
    
  // ativa registro de acesso caso solicitado
  if(option.MemReg)
    ativaMemLog();
  else
    desativaMemLog();
  
  // abre arquivos de entrada e de saída
  erroAssert(option.FileIn != "", "Endereço do arquivo de entrada é inválido");
  std::ifstream FileIn = OpenInFiles(&option);
  erroAssert(option.FileOut != "", "Endereço do arquivo de saída é inválido");
  std::ofstream FileOut = OpenOutFiles(&option);

  LineProcessor LP;
  // obtenção do tamanho da tabela Hash
  int HashSize;
  HashSize = LP.getHashSize(FileIn);
  erroAssert(HashSize > 0, "Tamanho da tabela Hash é inválida");

  // criação da tabela conforme o parâmetro passado
  defineFaseMemLog(0);
    Hash HashTable(HashSize);
    HashTable.AccessHash();

  // realização das ações descritas no arquivo
  defineFaseMemLog(1);
    LP.getTexts(FileIn, &HashTable, FileOut);
    HashTable.AccessHash();
  
  // fecha arquivos
  FileIn.close();
  avisoAssert(!FileIn.is_open(), "Arquivo de entrada não foi fechado corretamente");
  FileOut.close();
  avisoAssert(!FileOut.is_open(), "Arquivo de saída não foi fechado corretamente");

  return 0;
}