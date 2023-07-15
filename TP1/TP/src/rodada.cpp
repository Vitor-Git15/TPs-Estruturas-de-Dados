#include "rodada.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#include <iostream>

int Rodada::getNumJogadores()
// Descricao: retorna o numero de jogadores da rodada
// Entrada: nao tem
// Saida: numero de jogadores participantes da rodada
{
  return this->_qtdJogadores;
}
void Rodada::setNumJogadores(int numJogadores)
// Descricao: seta o numero de jogadores que participarão da rodada
// Entrada: numero de jogadores que participarão da rodada
// Saida: nao tem
{
  erroAssert(numJogadores > 0, "Numero de jogadores inválido");
  this->_qtdJogadores = numJogadores;
}

void Rodada::addPote(int val)
// Descricao: adiciona o valor val ao pote
// Entrada: valor a ser adicionado no pote
// Saida: nao tem
{
  _pote += val;
}
void Rodada::setPingo(int pingo)
// Descricao: seta o pingo da rodada
// Entrada: valor do pingo
// Saida: nao tem
{
  this->_pingo = pingo;
}
int Rodada::getPingo()
// Descricao: retorna o valor do pingo da rodada
// Entrada: nao tem
// Saida: valor do pingo
{
  return this->_pingo;
}

Jogador* Rodada::getJogadores()
// Descricao: retorna o jogador com maior pontuação da rodada
// Entrada: nao tem
// Saida: primeiro jogador da rodada
{
  return Jogadores->getJogadorHead()->prox_j;
}

void Rodada::addVencedores()
// Descricao: seta a quantidade de vencedores de uma rodada
// Entrada: nao tem
// Saida: quantidade de jogadores de uma rodada é adicionado em "numVencedores"
{
  Jogador* j;
  j = Jogadores->getJogadorHead()->prox_j;
  _qtdVencedores = 0;
  while(j != nullptr){
    
    if(j->getPontuacao() == Jogadores->getJogadorHead()->prox_j->getPontuacao()){
      if((j->getPontuacao() >= FHPONTUACAO && j->getPontuacao() < FKPONTUACAO) && (j->parMaior() == Jogadores->getJogadorHead()->prox_j->parMaior())){
        _qtdVencedores++;
      } else if((j->getPontuacao() >= TPPONTUACAO && j->getPontuacao() < TKPONTUACAO) && (j->parMaior() == Jogadores->getJogadorHead()->prox_j->parMaior())) {
        _qtdVencedores++;
      } else if(j->highCard() == Jogadores->getJogadorHead()->prox_j->highCard()){
        _qtdVencedores++;
      } else{
        break;
      }
    }else if(j->getPontuacao() < Jogadores->getJogadorHead()->prox_j->getPontuacao()){
      break;
    }

    j = j->prox_j;
  }
}

void Rodada::printaVencedores(Partida* P, std::ofstream& out)
// Descricao: adiciona o valor ganho e determinada rodada e o nome dos vencedores da rodada
// Entrada: ponteiro para a partida e o arquivo de saída
// Saida: dados escritos no arquivo de saída
{
  erroAssert(P != nullptr, "Referência à partida é invalida");
  erroAssert(out, "Arquivo de saída inválido");
  this->addVencedores();

  Jogador* j;
  j = Jogadores->getJogadorHead()->prox_j;
  int ganho;
  ganho = this->_pote/_qtdVencedores;
  out << this->_qtdVencedores << " " << ganho << " " << j->_classificacao << std::endl;
  for(int i = 0; i < this->_qtdVencedores; i++){
    out << j->getName() << std::endl;

    Rodada* r = P->_Rodadas->getRodadaHead()->prox_r;
    Jogador* j1 = r->Jogadores->getJogadorHead()->prox_j;
    while(j1 != nullptr){

      if(j1->getName() == j->getName()){
        j->addDinheiro(ganho);
        j1->setDinheiro(j->getDinheiro());
        break;
      }

      j1 = j1->prox_j;
    }
    j = j->prox_j;
  }
  
}

int Rodada::getRodada()
// Descricao: retorna o id da rodada (inicia em 1 e vai até n)
// Entrada: nao tem
// Saida: id da rodada
{
  return this->_id;
}
void Rodada::setRodada(int rodada)
// Descricao: seta o id da rodada (inicia em 1 e vai até n)
// Entrada: id da rodada
// Saida: nao tem
{
  this->_id = rodada;
}

Jogador* Rodada::addJogador(const std::string &nome, const std::string &cartas, int val)
// Descricao: adiciona um jogador a rodada
// Entrada: nome do jogador, suas cartas e seu montante na rodada
// Saida: ponteiro para o jogador adicionado
{
  if(Jogadores == nullptr)
    Jogadores = new ListaJogadores;
  return Jogadores->addJogador(nome, cartas, val);
}

Rodada* ListaRodadas::getRodadaHead()
// Descricao: retorna o ponteiro à cabeça da lista de rodadas
// Entrada: nao tem
// Saida: ponteiro à cabeça da lista de rodadas
{
  erroAssert(Rodada_head != nullptr, "Erro no retorno da rodada");
  return Rodada_head;
}
Rodada* ListaRodadas::getRodadaAtual()
// Descricao: retorna o ponteiro à rodada atual
// Entrada: nao tem
// Saida: ponteiro à rodada atual
{
  erroAssert(Rodada_atual != nullptr, "Erro no retorno da rodada");
  return Rodada_atual;
}
void ListaRodadas::setnewRodada(int pingo)
// Descricao: Adiciona uma nova rodada a lista de rodadas
// Entrada: valor do pingo
// Saida: nao tem
{

  Rodada* nova;
  nova = new Rodada;
  nova->setPingo(pingo);
  ESCREVEMEMLOG((long int)(nova),sizeof(double),2);
  if(getRodadaHead()->prox_r == nullptr){
    getRodadaHead()->prox_r = new Rodada;
    getRodadaHead()->prox_r = nova;
    Rodada_atual = getRodadaHead()->prox_r;
  } else{
    Rodada* aux;
    aux = Rodada_atual;
    aux->prox_r = new Rodada;
    aux->prox_r = nova;
    Rodada_atual = Rodada_atual->prox_r;
  }
  
}
Jogador* Rodada::setJogador(const std::string &nome, const std::string &cartas, Partida* P)
// Descricao: adiciona um novo jogador a uma rodada caso ele seja um dos participantes da partida
// Entrada: nome do jogador suas cartas e um ponteiro a partida partida
// Saida: ponteiro ao jogador adicionado
{
  erroAssert(P != nullptr, "Referência à partida é invalida");
  Rodada* r;
  r = P->_Rodadas->getRodadaHead()->prox_r;
  Jogador* j;
  j = r->Jogadores->getJogadorHead();
  
  
  while(j != nullptr){
    if(j->getName() == nome){
      return P->getRodadaAtual()->addJogador(nome, cartas, j->getDinheiro());
    }
    j = j->prox_j;
  }
  return nullptr;
}

void Rodada::pingar(Partida* P){
  //Antes de pingar precisamos verificar se o pingo é válido, ou seja, todos tem condição de pagar

  //Valor que cada jogador, a cada rodada, deve colocar no pote
  //O valor minimo do pingo é 50
  //Todo jogador deve pigar a cada jogada, mesmo não participando dela
  erroAssert(P != nullptr, "Referência à partida é invalida");

  Jogador* j;
  j = P->_Rodadas->getRodadaHead()->prox_r->Jogadores->Jogador_head;
  j = j->prox_j;

  while(j != nullptr){
    j->rmvDinheiro(this->_pingo);
    this->addPote(this->_pingo);

    

    j = j->prox_j;
  }

  j = this->Jogadores->Jogador_head;
  j = j->prox_j;

  Rodada* r = P->_Rodadas->getRodadaHead()->prox_r;
  Jogador* j1 = r->Jogadores->getJogadorHead()->prox_j;

  while(j != nullptr){
    
    while(j1 != nullptr){

      if(j1->getName() == j->getName()){
        j1->setDinheiro(j->getDinheiro());
        
        break;
      }
      
      j1 = j1->prox_j;
    }
    
    j = j->prox_j;
  }
}

bool Rodada::canPingar(Partida* p)
// Descricao: verifica se as condições para todos os jogadores pingarem são válidas
// Entrada: Ponteiro a partida
// Saida: true se puderem e false caso contrário
{
  erroAssert(p != nullptr, "Referência à partida é invalida");

  Jogador* j;
  j = p->_Rodadas->getRodadaHead()->prox_r->Jogadores->Jogador_head;
  j = j->prox_j;
  if(this->_pingo < 50){
    avisoAssert(this->_pingo > 50, "Valor do pingo é invalido");
    return false;
  }

  while(j != nullptr){
    if(j->getDinheiro() < this->_pingo){
      avisoAssert(j->getDinheiro() > this->_pingo, "Saldo insuficiente");
      return false;
    }
    
    j = j->prox_j;
  }
  return true;
}
bool Rodada::canApostar(int* aposta)
// Descricao: verifica se o jogador pode pingar o valor solicitado
// Entrada: vetor com os valores da aposta de cada jogador
// Saida: true se puderem e false caso contrário
{
  Jogador* j;
  j = this->Jogadores->Jogador_head;
  j = j->prox_j;
  
  int count = 0;
  while(j != nullptr){
    if((aposta[count]%50)){
      std::cout << aposta[count] << " " << j->getName() << std::endl;
      avisoAssert(!aposta[count]%50, "Valor da aposta é invalido");
      return false;
    } else if((aposta[count]) <= 0){
      std::cout << aposta[count] << " " << j->getName() << std::endl;
      avisoAssert(aposta[count] > 0, "Valor da aposta é invalido");
      return false;
    }
      
    else if(j->getDinheiro() < aposta[count])
      return false;

    
    j = j->prox_j;
    count++;
  }
  return true;
}

void Rodada::apostar(int* aposta, Partida* P)
// Descricao: realiza a aposta do jogadores
// Entrada: vetor com as apostas dos jogadores participantes e ponteiro a partida
// Saida: nao tem
{
  Jogador* j;
  j = this->Jogadores->Jogador_head;
  j = j->prox_j;
  
  int count = 0;
  
  while(j != nullptr){
    j->apostar(aposta[count], P);
    j = j->prox_j;
    
    count++;
  }
  j = this->Jogadores->Jogador_head;
  j = j->prox_j;

  Rodada* r = P->_Rodadas->getRodadaHead()->prox_r;
  Jogador* j1 = r->Jogadores->getJogadorHead()->prox_j;

  while(j != nullptr){
    
    while(j1 != nullptr){

      if(j1->getName() == j->getName()){
        j1->setDinheiro(j->getDinheiro());
        break;
      }

      j1 = j1->prox_j;
    }

    j = j->prox_j;
  }
}

void ListaRodadas::rmvRodadaAtual()
// Descricao: remove a rodada atual da lista de rodadas
// Entrada: nao tem
// Saida: nao tem
{
  Rodada* aux;
  aux = Rodada_head;
  while(aux->prox_r != this->getRodadaAtual()){
    aux = aux->prox_r;
   
  }
  this->Rodada_atual = aux;
  delete aux->prox_r;
  aux->prox_r = nullptr;
}
