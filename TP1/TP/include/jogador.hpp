//---------------------------------------------------------------------
// Arquivo	: jogadores.hpp
// Conteudo	: implementacao do TAD JOGADORES
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-05-19 - arquivo criado
//---------------------------------------------------------------------

#ifndef JOGADOR
#define JOGADOR

#include <string>

#include "carta.hpp"
#include "rodada.hpp"
#include "partida.hpp"

#define RSFPONTUACAO 1000
#define SFPONTUACAO 900
#define FKPONTUACAO 800
#define FHPONTUACAO 700
#define FPONTUACAO 600
#define SPONTUACAO 500
#define TKPONTUACAO 400
#define TPPONTUACAO 300
#define OPPONTUACAO 200

class ListaJogadores;

class Jogador{
  public:

    Jogador(): _nome(" "), _dinheiro(-1), _mao(nullptr), _pontuacao(-1), _classificacao(" "), prox_j(nullptr){}

    void apostar(int valAposta, Partida* P);
    //A aposta deve ser não nula e múltipla de 50
    //todos devem apostar na primeira jogada
    //Valor que cada jogador, a cada rodada, deve colocar no pote
    //O valor minimo do pingo é 50
    //Todo jogador deve pigar a cada jogada, mesmo não participando dela

    ListaCartas* getMao();
    void setMao(std::string cartas);
    void ordenaMao();

    int getDinheiro();
    void setDinheiro(int dinheiro);

    void setName(const std::string &nome);
    std::string getName();

    void addDinheiro(int val);
    void rmvDinheiro(int val);
  
    void setPontuacao(int pontuacao);
    void countPontuacao();
    int getPontuacao();

    bool sameNaipe();

    bool have_RSF();
    bool have_SF();
    int have_FK();
    int have_FH();
    bool have_F();
    bool have_S();
    int have_TK();
    int have_TP();
    int have_OP();
    int highCard();
    int parMaior();
  private:

    std::string _nome;
    int _dinheiro;
    ListaCartas* _mao;
    int _pontuacao;
    std::string _classificacao;
    Jogador* prox_j;

    friend class Partida;
    friend class Rodada;
    friend class ListaJogadores;
};

class ListaJogadores{
  public:
    ListaJogadores(): Jogador_head(new Jogador()), _qtdJogadores(0){}

    Jogador* addJogador(const std::string &nome, const std::string &cartas, int val);
    Jogador* Posiciona(int pos, bool antes);
    Jogador* getJogadorHead();

    void inserirDepois(Jogador* novo, Jogador* anterior);

  private:
    Jogador* Jogador_head;
    int _qtdJogadores;

    friend class Jogador;
    friend class Rodada;
};

#endif