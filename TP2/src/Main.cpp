#include "LexOrder.hpp"
#include "QuickSort.hpp"
#include "WordsList.hpp"
#include "LineProcessor.hpp"
#include "SelectionSort.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstring>

#define DEFAULTMAXTAM 5

// struct responsável por armazenar as opções passadas ao executar o programa
struct opt{

  int Median = DEFAULTMEDIAN;
  int MaxTamPartition = DEFAULTMAXTAM;

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
  std::cout << "\t -[m|M] - Valor para busca da mediana\t" << std::endl;
  std::cout << "\t -[s|S] - Tamanho máximo das partições\t" << std::endl;
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

  while((option = getopt(argc, argv, "i:I:m:M:s:S:o:O:p:P:l:L")) != EOF){

    // arquivo de entrada com o texto a ser processado e a nova ordem lexicográfica 
    if(option == 'i' || option == 'I'){
      options->FileIn = optarg;
    }

    // quantidade de elementos a ser comparado para escolha da mediana
    else if(option == 'm' || option == 'M'){
      options->Median = std::stoi(optarg);
    }

    // tamanho máximo das partições de menor tamanho
    else if(option == 's' || option == 'S'){
      options->MaxTamPartition = std::stoi(optarg);
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

int main(int argc, char **argv){
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

  // definição das classes utilizadas
  Order LexOrder;
  ListWords List; 
  LineProcessor LP;

  // passagem de parâmetros
  defineFaseMemLog(0);
    LP.getTexts(FileIn, &LexOrder, &List);
    erroAssert(List.First != nullptr, "Falha na atribuição do texto");
    List.ListAccess();
  // ordenação por método simples ou complexo
  defineFaseMemLog(1);
    if(List.total > option.MaxTamPartition){
      List.ListAccess();
      QuickSort QS(&List, option.Median, option.MaxTamPartition, &LexOrder);
    }
    else{
      List.ListAccess();
      SelectionSort SS(&List, &LexOrder);
    }
  // impressão da lista
  defineFaseMemLog(2);
    List.ListAccess();
    List.Print(FileOut);

  // fecha arquivos
  FileIn.close();
  avisoAssert(!FileIn.is_open(), "Arquivo de entrada não foi fechado corretamente");
  FileOut.close();
  avisoAssert(!FileOut.is_open(), "Arquivo de saída não foi fechado corretamente");

  return 0;
}