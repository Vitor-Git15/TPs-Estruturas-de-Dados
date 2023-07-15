//---------------------------------------------------------------------
// Arquivo	: jogadores.hpp
// Conteudo	: implementacao do TAD JOGADORES
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-05-19 - arquivo criado
//---------------------------------------------------------------------

#ifndef RODADA
#define RODADA

#include <fstream>

#include "carta.hpp"
#include "jogador.hpp"
#include "partida.hpp"

class Jogador;
class Partida;
class ListaJogadores;
class ListaRodadas;

class Rodada{
  public:
  Rodada(): Jogadores(nullptr), prox_r(nullptr), _id(0), _pingo(0) , _qtdJogadores(0), _qtdVencedores(0), _pote(0){}
    
    int getNumJogadores();
    void setNumJogadores(int numJogadores);

    Jogador* getJogadores();

    void setRodada(int rodada);
    int getRodada();
    void addVencedores();

    Jogador* addJogador(const std::string &nome, const std::string &cartas, int val);
    Jogador* setJogador(const std::string &nome, const std::string &cartas, Partida* P);

    void setPingo(int pingo);
    int getPingo();

    void addPote(int val);

    bool canPingar(Partida* p);
    bool canApostar(int* aposta);
    void pingar(Partida* p);
    void apostar(int* aposta, Partida* P);

    void printaVencedores(Partida* P, std::ofstream& out);
  private:

    ListaJogadores* Jogadores;

    Rodada* prox_r;

    int _id;
    int _pingo;
    int _qtdJogadores;
    int _qtdVencedores;
    int _pote;
    
    friend class Partida;
    friend class Jogador;
    friend class ListaRodadas;
};

class ListaRodadas{
public:
    ListaRodadas(): Rodada_head(new Rodada()), Rodada_atual(new Rodada()){}

    void setnewRodada(int pingo);
    Rodada* getRodadaHead();
    Rodada* getRodadaAtual();
    void rmvRodadaAtual();

  private:
    Rodada* Rodada_head;
    Rodada* Rodada_atual;
    friend class Jogador;
};

#endif