//---------------------------------------------------------------------
// Arquivo	: jogadores.hpp
// Conteudo	: implementacao do TAD JOGADORES
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-05-19 - arquivo criado
//---------------------------------------------------------------------

#ifndef PARTIDA
#define PARTIDA

#include "carta.hpp"
#include "jogador.hpp"
#include "rodada.hpp"

class Rodada;
class Jogador;
class ListaRodadas;

class Partida{
  public:
    Partida():  _Rodadas(nullptr), _numJogadores(0), _numRodadas(0),  _valInicial(0){}

    int getRodadas();
    void setRodadas(int rodadas);
    void newRodada(int pingo);

    void newJogador();

    int getNumJogadores();
    void setNumJogadores(int numJogadores);

    void setValInicial(int valInicial);
    int getValInicial();

    void rmvRodadaAtual();
    void printaResult(std::ofstream& out);
    void rmvJogador();

    Rodada* getRodadaAtual();

  private:
    ListaRodadas* _Rodadas;
    
    int _numJogadores;
    int _numRodadas;
    int _valInicial;

    friend class Rodada;
    friend class Jogador;
};

#endif