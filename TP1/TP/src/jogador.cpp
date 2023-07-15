#include "jogador.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#include <cstring>
#include <sstream>
#include <iostream>

void Jogador::apostar(int valAposta, Partida* P)
// Descricao: Faz a aposta do jogador em determinada rodada
// Entrada: valor da aposta e um ponteiro da partida corrente
// Saida: nao tem
{
  erroAssert(P != nullptr, "Referência à partida é invalida");
  this->rmvDinheiro(valAposta);
  P->getRodadaAtual()->addPote(valAposta);

  Rodada* r = P->_Rodadas->getRodadaHead()->prox_r;
  Jogador* j = r->Jogadores->getJogadorHead()->prox_j;
  while(j != nullptr){
    if(j->getName() == this->getName()){
      j->setDinheiro(this->getDinheiro());
    }
    j = j->prox_j;
  }
}

void Jogador::setName(const std::string &nome)
// Descricao: Seta o nome do jogador
// Entrada: nome
// Saida: nao tem
{
  this->_nome = nome;
}
std::string Jogador::getName()
// Descricao: retorna o nome do jogador
// Entrada: nao tem
// Saida: nome do jogador
{
  return this->_nome;
}

void Jogador::setMao(std::string cartas)
// Descricao: Seta as cartas do jogador
// Entrada: string com as 5 cartas
// Saida: nao tem
{
  std::stringstream stream(cartas);
  std::string carta;

  this->_mao = new ListaCartas;

  while(stream>>carta){

    int num;
    char naipe;

    std::stringstream _stream(carta);
    std::string aux;
    naipe = carta[carta.size()-1];
    
    getline(_stream, aux, naipe);

    std::istringstream(aux) >> num;

    this->_mao->setnewCarta(num , naipe);
  }
}
ListaCartas* Jogador::getMao()
// Descricao: retorna um ponterio para a lista de cartas do jogador
// Entrada: nao tem
// Saida: ponteiro a lista de cartas do jogador
{
  return this->_mao;
}

int Jogador::getDinheiro()
// Descricao: Retorna o dinheiro do jogador
// Entrada: nao tem
// Saida: quantia de dinheiro do jogador
{
  return this->_dinheiro;
}
void Jogador::setDinheiro(int dinheiro)
// Descricao: seta o montante do jogador ao valor "dinheiro"
// Entrada: dinheiro a ser setado ao montante
// Saida: nao tem
{
  avisoAssert(dinheiro >= 0, "Valor do dinheiro setado é inválido");
  this->_dinheiro = dinheiro;
}

void Jogador::addDinheiro(int val)
// Descricao: adiciona um valor "val" ao montante do jogador 
// Entrada: valor a ser adicionado
// Saida: nao tem
{
  avisoAssert(val >= 0, "Valor do dinheiro adicionado é inválido");
  this->_dinheiro += val;
}
void Jogador::rmvDinheiro(int val)
// Descricao: remove um valor "val" ao montante do jogador 
// Entrada: valor a ser removido
// Saida: nao tem
{
  avisoAssert(this->_dinheiro >= val, "Valor a ser removido é maior que o possuído");
  avisoAssert(val >= 0, "Valor do dinheiro removido é inválido");
  this->_dinheiro -= val;
}

void Jogador::countPontuacao()
// Descricao: pega a classificação do jogador
// Entrada: nao tem
// Saida: nao tem
{

  if (this->have_RSF()){
    this->_pontuacao = RSFPONTUACAO;
    this->_classificacao = "RSF";
  }
  else if (this->have_SF()){
    this->_pontuacao = SFPONTUACAO;
    this->_classificacao = "SF";
  }

  else if (this->have_FK()){
    this->_pontuacao = FKPONTUACAO + this->have_FK();
    this->_classificacao = "FK";
    }

  else if (this->have_FH()){
    this->_pontuacao = FHPONTUACAO + this->have_FH();
    this->_classificacao = "FH";
  }

  else if (this->have_F()){
    this->_pontuacao = FPONTUACAO;
    this->_classificacao = "F";
  }

  else if (this->have_S()){
    this->_pontuacao = SPONTUACAO;
    this->_classificacao = "S";
  }

  else if (this->have_TK()){
    this->_pontuacao = TKPONTUACAO + this->have_TK();
    this->_classificacao = "TK";
  }

  else if (this->have_TP()){
    this->_pontuacao = TPPONTUACAO + this->have_TP();
    this->_classificacao = "TP";
  }

  else if (this->have_OP()){
    this->_pontuacao = OPPONTUACAO + this->have_OP();
    this->_classificacao = "OP";
  }

  else{
    this->_classificacao = "HC";
  }
  
}

void Jogador::setPontuacao(int pontuacao)
// Descricao: seta a pontuação do jogador
// Entrada: pontuação a ser setada
// Saida: nao tem
{
  this->_pontuacao = pontuacao;
}

int Jogador::getPontuacao()
// Descricao: retorna a pontuação do jogador
// Entrada: não tem
// Saida: pontuação do jogador
{
  return this->_pontuacao;
}

bool Jogador::sameNaipe()
// Descricao: função booleana que retorna true se a mão do jogador for do mesmo naipe e false caso contrário
// Entrada: nao tem
// Saida: nao tem
{
  Carta* aux;
  aux = _mao->Carta_head->prox;

  char naipe;
  naipe = aux->getNaipe();

  while(aux != nullptr){
    if(aux->getNaipe() != naipe){
      return false;
    }
    aux = aux->prox;
  }
  return true;
}

bool Jogador::have_RSF()
// Descricao: verifica se a classificação do jogador é um Royal Straight Flush
// Entrada: nao tem
// Saida: true se sim, false se não for
{

  if(!sameNaipe()){
    return false;
  }

  Carta* aux;
  aux = this->_mao->Carta_head->prox;
  
  for (int i = 9; i <= 13; i++){
    if(i == 9 && aux->getNumero() == 1){
      aux = aux->prox;
      continue;
    } else if((aux->getNumero() != i) || (i == 9 && aux->getNumero() == 9)){
      return false;
    }
    aux = aux->prox;
  }
  return true;
}
bool Jogador::have_SF()
// Descricao: verifica se a classificação do jogador é um Stright Flush
// Entrada: nao tem
// Saida: true se sim, false se não for
{
  if(!sameNaipe()){
    return false;
  }

  Carta* aux;
  aux = this->_mao->Carta_head->prox;
  int fnum = aux->getNumero();

  for(int i = 0 ; i <= 4; i++){
    if((aux->getNumero() - fnum) != i){
      return false;
    }
    aux = aux->prox;
  }
  return true;
}
int Jogador::have_FK()
// Descricao: verifica se a classificação do jogador é um Four of a Kind
// Entrada: nao tem
// Saida: retorna o valor da quádrupla
{
  if(sameNaipe()){
    return 0;
  }

  Carta* f_card;
  f_card = this->_mao->Carta_head->prox;

  Carta* pu_card;
  pu_card = f_card;
  for (int i = 1; i < 4; i++){
    pu_card = pu_card->prox;
  }

  if(f_card->getNumero() == f_card->prox->getNumero() && f_card->getNumero() == pu_card->getNumero()){
    return f_card->getNumero();
  } else if(f_card->getNumero() != f_card->prox->getNumero() && f_card->prox->getNumero() == pu_card->prox->getNumero()){
    return f_card->prox->getNumero();
  }
  return 0;

}

int Jogador::have_FH()
// Descricao: verifica se a classificação do jogador é um Full House
// Entrada: nao tem
// Saida: retorna o valor da maior tripla
{
  if(sameNaipe()){
    return 0;
  }
  
  Carta* aux;
  aux = _mao->Carta_head->prox;

  int num = aux->getNumero();

  int qtd_ig_p = 0;

  while(aux != nullptr){
    if(aux->getNumero() != num)
      break;
    qtd_ig_p++;
    aux = aux->prox;
  }

  int trinca;
  if(qtd_ig_p == 3)
    trinca = num; 
  else if(qtd_ig_p != 2 && qtd_ig_p != 3)
    return 0;
  
  num = aux->getNumero();
  int qtd_ig_s = 0;

  while(aux != nullptr){

    if(aux->getNumero() != num)
      return 0;

    qtd_ig_s++;
    aux = aux->prox;

  }

  if(qtd_ig_s == 3)
    trinca = num;
  return trinca;
}
bool Jogador::have_F()
// Descricao: verifica se a classificação do jogador é um Flush
// Entrada: nao tem
// Saida: true se sim, false se não for
{
  return sameNaipe();
}
bool Jogador::have_S()
// Descricao: verifica se a classificação do jogador é um Stright
// Entrada: nao tem
// Saida: true se sim, false se não for
{
  Carta* aux;
  aux = this->_mao->Carta_head->prox;
  int fnum = aux->getNumero();

  for(int i = 0 ; i <= 4; i++){
    if((aux->getNumero() - fnum) != i){
      return false;
    }
    aux = aux->prox;
  }
  return true;
}
int Jogador::have_TK()
// Descricao: verifica se a classificação do jogador é um Three of a Kind
// Entrada: nao tem
// Saida: retorna o valor da maior tripla
{
  Carta* f_card;
  Carta* t_card;
  Carta* l_card;

  f_card = this->_mao->Carta_head->prox;
  t_card = f_card->prox->prox;
  l_card = t_card->prox->prox;

  if(f_card->getNumero() == t_card->getNumero())
    return f_card->getNumero();
  else if(t_card->getNumero() == l_card->getNumero())
    return t_card->getNumero();
  else
    return 0;
}
int Jogador::have_TP()
// Descricao: verifica se a classificação do jogador é um Two Pairs
// Entrada: nao tem
// Saida: retorna o valor do maior par
{
  Carta* c;
  c = this->_mao->Carta_head->prox;
  int duplas = 0;
  int maiorDupla;
  while(c->prox != nullptr){
    if(c->getNumero() == c->prox->getNumero()){
      duplas++;
      maiorDupla = c->getNumero();
      c = c->prox;
      break;
    }
    c = c->prox;
  }
  while(c->prox != nullptr){
    if(c->getNumero() == c->prox->getNumero()){
      duplas++;
      if(c->getNumero() > maiorDupla)
        maiorDupla = c->getNumero();
      c = c->prox;
      break;
    }
    c = c->prox;
  }
  if(duplas == 2)
    return maiorDupla;
  return 0;
}
int Jogador::have_OP()
// Descricao: verifica se a classificação do jogador é um One Pair
// Entrada: nao tem
// Saida: true se sim, false se não for
{
  Carta* aux;
  aux = _mao->Carta_head->prox;
  while(aux->prox != nullptr){
    if(aux->getNumero() == aux->prox->getNumero())
      return aux->getNumero();
    aux = aux->prox;
  }
  return 0;
}
int Jogador::highCard()
// Descricao: retorna a maior carta do jogador
// Entrada: nao tem
// Saida: número da maior carta do jogador
{
  Carta* aux;
  aux = this->_mao->Carta_head->prox;
  
  while(aux->prox != nullptr){
    aux = aux->prox;
  }

  return aux->getNumero();
}

int Jogador::parMaior()
// Descricao: verifica os pares do jogador e retorna o maior deles
// Entrada: nao tem
// Saida: maior par do jogador
{
  Carta* aux;
  aux = _mao->Carta_head->prox;
  if(aux->getNumero() != aux->prox->getNumero() && aux->prox != nullptr)
    aux = aux->prox;
  int num = aux->getNumero();

  int qtd_ig_p = 0;

  while(aux != nullptr){
    if(aux->getNumero() != num)
      break;
    qtd_ig_p++;
    aux = aux->prox;
  }

  if(aux->getNumero() != aux->prox->getNumero() && aux->prox != nullptr)
    aux = aux->prox;
  
  int minDupla = 14;
  if(qtd_ig_p == 2)
    minDupla = num;
  
  num = aux->getNumero();
  int qtd_ig_s = 0;

  while(aux != nullptr){

    if(aux->getNumero() == num)
      qtd_ig_s++;
    aux = aux->prox;
  }

  if(qtd_ig_s == 2 && minDupla > num)
    minDupla = num;

  return minDupla;
}

Jogador* ListaJogadores::getJogadorHead()
// Descricao: retorna a cabeça da lista de jogadores
// Entrada: nao tem
// Saida: cabeça da lista de jogadores
{
  erroAssert(Jogador_head != nullptr, "Jogador inexistente");
  return Jogador_head;
}

void ListaJogadores::inserirDepois(Jogador* novo, Jogador* anterior)
// Descricao: Insere um novo jogador a frete do jogador anterior passado
// Entrada: Jogador a ser inserido e jogador anterior a posição de inserção
// Saida: nao tem
{
  erroAssert(novo != nullptr, "Impossivel inserir o jogador");
  erroAssert(anterior != nullptr, "Posição de inserção do jogador é inválida");
  novo->prox_j = anterior->prox_j;
  anterior->prox_j = novo;
}
Jogador* ListaJogadores::addJogador(const std::string &nome, const std::string &cartas, int val)
// Descricao: Adiciona um novo jogador de forma ordenada pela pontuação na lista de jogadores
// Entrada: nome, cartas e montante inicial do jogador
// Saida: Ponteiro ao jogador adicionado
{
  Jogador* novo;
  novo = new Jogador;

  novo->setName(nome);
  novo->setDinheiro(val);
  novo->setMao(cartas);
  ESCREVEMEMLOG((long int)(novo),sizeof(double),1);
  novo->countPontuacao();

  if(this->Jogador_head->prox_j == nullptr){

    inserirDepois(novo, Jogador_head);
    
    this->_qtdJogadores++;
    
  } else {

    Jogador* aux;
    aux = this->Jogador_head->prox_j;

    int pos = 1;

    while(aux != nullptr){

      if(novo->getPontuacao() > aux->getPontuacao()){
        Jogador* j;
        j = this->Posiciona(pos, true);
        
        inserirDepois(novo, j);

        this->_qtdJogadores++;
        
        break;

      } else if(novo->getPontuacao() == aux->getPontuacao()){
        
          if((novo->getPontuacao() >= FHPONTUACAO && novo->getPontuacao() < FKPONTUACAO) && (novo->parMaior() > aux->parMaior())){
              Jogador* j;
              j = this->Posiciona(pos, true);
              
              inserirDepois(novo, j);
              this->_qtdJogadores++;
          } else if((novo->getPontuacao() >= TPPONTUACAO && novo->getPontuacao() < TKPONTUACAO)&& (novo->parMaior() > aux->parMaior())) {
              Jogador* j;
              j = this->Posiciona(pos, true);
              
              inserirDepois(novo, j);
              this->_qtdJogadores++;
          }

          else if((novo->getPontuacao() >= FHPONTUACAO && novo->getPontuacao() < FKPONTUACAO) && (novo->parMaior() < aux->parMaior()));
          else if((novo->getPontuacao() >= TPPONTUACAO && novo->getPontuacao() < TKPONTUACAO)&& (novo->parMaior() < aux->parMaior()));

          else if(novo->highCard() >= aux->highCard()){
            Jogador* j;
            j = this->Posiciona(pos, true);
            
            inserirDepois(novo, j);
            this->_qtdJogadores++;
            break;
          }
      } 
      if(aux->prox_j == nullptr){
        inserirDepois(novo, aux);
        this->_qtdJogadores++;
        
        break;
      }
      
      aux = aux->prox_j;
      pos++;
    }
  }
  erroAssert(novo != nullptr, "Erro na adição do jogador");
  return novo;
}
Jogador* ListaJogadores::Posiciona(int pos, bool antes)
// Descricao: posiciona um ponteiro na lista de acordo com a posição solicitada
// Entrada: posição e valor booleano se vai ser anterior a posição ou nela
// Saida: ponteiro na posição desejada
{

  Jogador* j;

  //Verificar se a posição é válida

  //Posiciona a célula anterior a desejada
  j = this->Jogador_head;
  for (int i = 1; i < pos; i++){
    
    j = j->prox_j;
  }
  
  if(!antes){
    j = j->prox_j;
  }
  erroAssert(j != nullptr, "Erro no posicionamento do jogador");
  return j;
}
