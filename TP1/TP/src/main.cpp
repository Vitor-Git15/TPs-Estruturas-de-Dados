#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include "jogador.hpp"
#include "rodada.hpp"
#include "partida.hpp"
#include "lineprocessor.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

std::ifstream abreArquivoEntrada(std::string nome_arq)
// Descricao: abre o arquivo de entrada
// Entrada: nome do arquivo a ser aberto
// Saida: arquivo de entrada
{
  std::ifstream arq;
  arq.open(nome_arq);
  erroAssert(arq, "Erro na Abertura do arquivo");

  return arq;
}
std::ofstream abreArquivoSaida(std::string nome_arq)
// Descricao: abre o arquivo de saída
// Entrada: nome do arquivo de saída
// Saida: arquivo de saída
{
  std::ofstream arq;
  arq.open(nome_arq);
  erroAssert(arq, "Erro na Criacao do arquivo");

  return arq;
}
void iniciarJogo(std::string str, Partida* Principal)
// Descricao: verifica a integridade dos valores de entrada e inicializa uma partida
// Entrada: linha que especifica a quantidade de partidas e o montante inicial dos jogadores
// Saida: nao tem
{
  Inicializacao fl_aux;
  if(fl_aux.linhaValida(str))
    Principal->setRodadas(fl_aux.processaLinha(str, Principal));
  else{
    erroAssert(0, "Inicialização incorreta");
  }
}
bool iniciarRodada(std::string str, Partida* Principal, int id)
// Descricao: verifica a integridade dos valores de entrada e inicializa uma rodada
// Entrada: linha que especifica a quantidade de jogadores e o valor do pingo
// Saida: true caso obtem-se sucesso e false caso contrário
{
  espRodada rd_aux;
  if(rd_aux.linhaValida(str)){
    rd_aux.processaLinha(str, Principal);
    return true;
  }
  return false;
}
int iniciarJogadores(std::string str, Partida* Principal)
// Descricao: verifica a integridade dos valores de entrada e inicializa os jogadores
// Entrada: linha que especifica o nome dos jogadores sua aposta e suas cartas
// Saida: valor da aposta
{
  espJogada jgd_aux;
  if(jgd_aux.linhaValida(str)){
    return jgd_aux.processaLinha(str, Principal);
  }
  return 0;
}
void parse_args(int argc, char **argv, Partida* Principal)
// Descricao: Passa os argumentos e realiza o jogo
// Entrada: argumentos passados na entrada e um ponteiro para a partida
// Saida: nao tem
{
  erroAssert(argc > 1, "Poucos argumentos foram apresentados");

  std::string str_aux;
  std::ifstream arq = abreArquivoEntrada(argv[1]);
  std::ofstream out = abreArquivoSaida("saida.txt");

  defineFaseMemLog(0);
  getline(arq, str_aux);
  iniciarJogo(str_aux, Principal);

  int rodada = 1;
  int rodada_valida = 1;
  while(Principal->getRodadas() >= rodada){
    getline(arq, str_aux);
    if(iniciarRodada(str_aux, Principal, rodada_valida)){
      Principal->getRodadaAtual()->setRodada(rodada_valida);
      int Apostas[Principal->getRodadaAtual()->getNumJogadores()];
      for(int i = 0; i < Principal->getRodadaAtual()->getNumJogadores(); i++){
        getline(arq, str_aux);
        Apostas[i] = iniciarJogadores(str_aux, Principal);
      }
      if(Principal->getRodadaAtual()->canPingar(Principal) && Principal->getRodadaAtual()->canApostar(Apostas)){
        Principal->getRodadaAtual()->pingar(Principal);
        Principal->getRodadaAtual()->apostar(Apostas, Principal);
        Principal->getRodadaAtual()->printaVencedores(Principal, out);
      } else{
        Principal->rmvRodadaAtual();
        rodada_valida--;
      }
      rodada_valida++;
      rodada++;
    }
  }
  Principal->printaResult(out);
  arq.close();
  out.close();
}

int main (int argc, char **argv)
// Descricao: Função main que incializa todo o programa
// Entrada: arumentos passados na chamada do programa
// Saida: 0 caso o programa ocorre corretamente e não zero caso contrário
{
  Partida Principal;
  char logoname[50] = "./saidap";
  iniciaMemLog(logoname);
  ativaMemLog();
  parse_args(argc, &*argv, &Principal);
  return 0;
}