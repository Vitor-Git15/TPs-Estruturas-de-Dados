#include "carta.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"
#include <iostream>

void ListaCartas::setnewCarta(int num, char naipe)
// Descricao: inicializa uma nova carta
// Entrada: número da carta e o naipe
// Saida: nao tem
{

  Carta* nova;
  nova = new Carta;
  nova->setNaipe(naipe);
  nova->setNumero(num);
  ESCREVEMEMLOG((long int)(nova),sizeof(double),0);
  avisoAssert(nova != nullptr, "Erro na adição de uma nova carta");
  if(this->Carta_head->prox == nullptr){

    this->Carta_head = new Carta;
    this->Carta_head->prox = new Carta;
    this->Carta_head->prox = nova;
    
  } else{

    Carta* c;
    c = this->Carta_head->prox;
    int pos = 1;
    while(c != nullptr){

      if(nova->getNumero() <= c->getNumero()){
        Carta* aux;
        aux = this->Posiciona(pos, true);
        
        nova->prox = new Carta;
        nova->prox = aux->prox;
        aux->prox = nova;

        break;
      } else if(c->prox == nullptr){
        c->prox = new Carta;
        c->prox = nova;
        break;
      }
      c = c->prox;
      pos++;
    }
  }
}
Carta* ListaCartas::Posiciona(int pos, bool antes)
// Descricao: Posiciona o ponteiro para a posição solicitada
// Entrada: posição desejada e valor booleano se deseja o ponteiro ao elemento anterior ou posterior
// Saida: Ponteiro para o elemento desejado
{
  Carta* c;

  //Posiciona a célula anterior a desejada
  c = this->Carta_head;
  for (int i = 1; i < pos; i++){
    c = c->prox;
  }
  //Se o valor booleano for false pararemos o ponteiro pra próxima carta
  if(!antes){
    c = c->prox;
  }
  erroAssert(c != nullptr, "Posicionamento da carta é inválido");
  return c;
}

void Carta::setNaipe(char naipe)
// Descricao: Seta o naipe da carta
// Entrada: naipe
// Saida: nao tem
{
  this->_naipe = naipe;
}
char Carta::getNaipe()
// Descricao: retorna o naipe da carta
// Entrada: nao tem
// Saida: naipe
{
  return this->_naipe;
}

void Carta::setNumero(int num)
// Descricao: seta o número da carta
// Entrada: número da carta
// Saida: nao tem
{
  this->_numero = num;
}
int Carta::getNumero()
// Descricao: retorna o número da carta
// Entrada: nao tem
// Saida: número da carta
{
  return this->_numero;
}
