#include "partida.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#include <iostream>

int Partida::getNumJogadores()
// Descricao: retorna o número de jogadores da partida
// Entrada: nao tem
// Saida: numero de jogadores da partida
{
  return this->_numJogadores;
}
void Partida::setNumJogadores(int numJogadores)
// Descricao: seta a quantidade de jogadores que a partida terá ao total
// Entrada: numero de jogadores total que irão jogar
// Saida: nao tem
{
  erroAssert(numJogadores > 0, "Numero de jogadores inválido");
  this->_numJogadores = numJogadores;
}

Rodada* Partida::getRodadaAtual()
// Descricao: retorna um ponteiro a rodada atual(a última jogada)
// Entrada: nao tem
// Saida: ponterio a rodada atual
{
  erroAssert(this->_Rodadas->getRodadaAtual() != nullptr, "Erro na atribução da rodada");
  return this->_Rodadas->getRodadaAtual();
}
int Partida::getRodadas()
// Descricao: retorna o número de rodadas que teram no total
// Entrada: nao tem
// Saida: numero de rodadas totais
{
  return this->_numRodadas;
}
void Partida::setRodadas(int rodadas)
// Descricao: seta o numero de rodadas que a partida terá
// Entrada: numero de rodadas totais
// Saida: nao tem
{
  erroAssert(rodadas > 0, "Numero de rodadas inválido");
  this->_numRodadas = rodadas;
}
void Partida::newRodada(int pingo)
// Descricao: adiciona uma nova rodada a partida caso satisfaça as condições
// Entrada: valor do pingo da rodada
// Saida: nao tem
{
  if(pingo < 50){
    avisoAssert(pingo >= 50, "Numero de jogadores inválido");
    return ;
  }
  if(_Rodadas == nullptr)
    _Rodadas = new ListaRodadas;
  _Rodadas->setnewRodada(pingo);
}

void Partida::setValInicial(int valInicial)
// Descricao: seta o valor inicial dos participantes
// Entrada: valor inicial dos participantes
// Saida: nao tem
{
  erroAssert(valInicial > 0, "Valor inicial inválido");
  this->_valInicial = valInicial;
}
int Partida::getValInicial()
// Descricao: retorna o valor inicial dos participantes
// Entrada: nao tem
// Saida: valor inicial dos participantes
{
  return this->_valInicial;
}
void Partida::rmvRodadaAtual()
// Descricao: remove a partida atual, geralmente chamada quando há alguma inconsistência na rodada
// Entrada: nao tem
// Saida: nao tem
{
  this->_Rodadas->rmvRodadaAtual();
}
void Partida::printaResult(std::ofstream& out)
// Descricao: insere no arquivo de saída os jogadores ordenados pelo seu montante
// Entrada: arquivo de saída
// Saida: dados no arquivo de saída
{
  Rodada* r = this->_Rodadas->getRodadaHead()->prox_r;
  Jogador* j = r->Jogadores->getJogadorHead();
  Jogador* ant = r->Jogadores->getJogadorHead();

  out << "####" << std::endl;
  while(r->Jogadores->getJogadorHead()->prox_j != nullptr){
    ant = r->Jogadores->getJogadorHead();
    j = r->Jogadores->getJogadorHead();
    Jogador* m;
    m = j;
    while (j->prox_j != nullptr){
      if(m->getDinheiro() < j->prox_j->getDinheiro()){
        m = j->prox_j;
        ant = j;
      }
      j = j->prox_j;
    }
    out << m->getName() << " " << m->getDinheiro() << std::endl;
    ant->prox_j = m->prox_j;
    delete m;
  }
}