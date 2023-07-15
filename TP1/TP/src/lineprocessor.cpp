#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>


#include "lineprocessor.hpp"
#include "msgassert.hpp"

bool Inicializacao::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\s*\\d+\\s\\d+\\s*");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

int Inicializacao::processaLinha(const std::string &str, Partida* Principal) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas duas variaveis abaixo:
  int rodadas, valorInicial;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> rodadas >> valorInicial;
  erroAssert(valorInicial >= 0, "Valor inicial inválido");
  erroAssert(rodadas > 0, "Numero de rodadas inválido");
  Principal->setValInicial(valorInicial);
  return rodadas;
}

bool espRodada::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Cada parte segue o padrao regular abaixo:
  //
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\d+\\s\\d+");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

int espRodada::processaLinha(const std::string &str, Partida* Principal) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas duas variaveis abaixo:
  int numJogadores, pingo;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> numJogadores >> pingo;

  avisoAssert(numJogadores > 0, "Numero de jogadores inválido");
  avisoAssert(pingo >= 50, "Pingo inválido");

  Principal->newRodada(pingo);
  Principal->getRodadaAtual()->setNumJogadores(numJogadores);
  return numJogadores;
}

bool espJogada::linhaValida(const std::string &str) const {
  std::regex regularExpr("(\\s*[a-zA-Z]+\\s*)*(\\s*[0-9]+\\s*)*(\\s*([1-9]|[1][0-3])[PECO]\\s*){5}");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

int espJogada::processaLinha(const std::string &str, Partida* Principal) {

  std::regex regularExprCard("([1-9]|[1][0-3])[PECO]{1}");
  std::regex regularExprName("[a-zA-Z]+");
  std::regex regularExprMoney("[0-9]+");

  std::stringstream stream(str);
  std::string out;

  std::string names = "";
  std::string cards = "";
  int aposta;
  while (stream >> out)
  {
    if(std::regex_match(out, regularExprCard)){
      cards += out + ' ';
    } else if(std::regex_match(out, regularExprName)){
      names += out + ' ';
    } else if(std::regex_match(out ,regularExprMoney)){
      std::stringstream val(out);
      val >> aposta;
    }
  }
  erroAssert(names.length() >= 1, "Nome invalido");
  erroAssert(cards.length() >= 1, "Erro na passagem das cartas");
  
  names.erase(names.length() - 1);
  if(Principal->getRodadaAtual()->getRodada() == 1){
    Rodada* atual;
    atual = Principal->getRodadaAtual();
    atual->addJogador(names, cards, Principal->getValInicial());
    return aposta;
  } else{
    
    Rodada* atual;
    atual = Principal->getRodadaAtual();
    atual->setJogador(names, cards, Principal);
    return aposta;
  }
}