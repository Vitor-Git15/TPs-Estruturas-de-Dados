//---------------------------------------------------------------------
// Arquivo	: jogadores.hpp
// Conteudo	: implementacao do TAD JOGADORES
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-05-19 - arquivo criado
//---------------------------------------------------------------------

#ifndef CARTA
#define CARTA

class ListaCartas;

class Carta{
  public:
    Carta(): _numero(-1), _naipe(' '), prox(nullptr){}
    Carta* getProx(){
      return this->prox;
    }
    void setNaipe(char naipe);
    char getNaipe();

    void setNumero(int num);
    int getNumero();

  private:

    int _numero;
    char _naipe;
    Carta* prox;

    friend class ListaCartas;
    friend class Jogador;
};

class ListaCartas{
  public:
    ListaCartas(): Carta_head(new Carta()){}

    void setnewCarta(int num, char nipe);
    Carta* Posiciona(int pos, bool antes);
    Carta* getCartaHead(){
      return Carta_head;
    }
  private:
    Carta* Carta_head;

    friend class Jogador;
};



#endif