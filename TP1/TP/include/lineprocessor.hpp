#ifndef LINE_PROCESSOR_H
#define LINE_PROCESSOR_H

#include <iostream>
#include <fstream>

#include "partida.hpp"
/**
 * \class LineProcessor
 *
 * \brief Esta classe usa o padrao de projetos template para implementar um
 * algoritmo que processa linhas de texto da entrada padrao.
 */
class LineProcessor {

  public:

    /**
     * \brief Determina se uma linha eh valida ou nao.
     * Este metodo deve ser implementado pela classe concreta. Cada classe
     * concreta pode usar um criterio diferente para verificar se uma linha eh
     * valida.
     * \param str a string que representa a linha de texto.
     */
    virtual bool linhaValida(const std::string &str) const = 0;

    /**
     * \brief Realiza o processamento de uma linha de texto.
     * \param str a string que representa a linha de texto.
     */
    virtual int processaLinha(const std::string &str, Partida* Principal) = 0;
};

/**
 * \class Inicializacao
 *
 * Esta classa le linhas contendo "rodadas e dinheiro inicial dos participantes",
 * sendo:
 * populacao: numero natural que representa a quantidade de habitantes do pais.
 * porcentagem_urbana: numero natural que representa um arredondamento da
 * porcentagem da populacao que vive em cidades.
 */
class Inicializacao: public LineProcessor {

  public:

    /**
     * Somente linhas no formato: <nome> <int> <int> sao validas.
     * Exemplos de linhas validas:
     * Afganistao 38928346 25
     *    Afganistao         38928346     25
     *
     * Qualquer caracter nao alfa-numerico torna um nome invalido.
     * Exemplos de linhas invalidas:
     * Afganist&atilde;o 38928346 25
     * Estados Unidos 318562093 96   // (note o espaco entre Estados e Unidos)
     */
    bool linhaValida(const std::string &str) const override;

    /**
     * Para cada linha valida, deve-se imprimir a frase:
     * "XX pessoas vevem no campo no PP", sendo XX a quantidade (piso inferior)
     * de pessoas que vivem na zona rural no pais PP.
     *
     * Exemplos:
     * Afganistao 38928346 25  -->
     * 29196259 pessoas vivem no campo no Afganistao
     * EstadosUnidos 331002651 83  -->
     * 56270450 pessoas vivem no campo no EstadosUnidos
     */
    int processaLinha(const std::string &str, Partida* Principal) override;
};

/**
 * \class ContadorNumNaturais
 *
 * Esta classe imprime a soma dos numeros encontrados em linhas que contem
 * somente numeros.
 */
class espRodada: public LineProcessor {

  public:

    /**
     * Uma linha valida deve conter somente numeros naturais. Os numeros podem
     * ser seguidos ou precedidos por qualquer quantidade de espacos.
     * Exemplos de linhas validas:
     * 1
     * 1  2     4 8
     *       0 0 0         0
     *
     * Exemplos de linhas invalidas:
     * -1 1 2    // (note o sinal negativo)
     * 1 +1 0    // (note o sinal positivo)
     * Um 1 2
     * 1 2.      // (note o ponto no final da linha)
     */
    bool linhaValida(const std::string &str) const override;

    /**
     * Imprime a soma de cada linha valida.
     * Exemplo:
     * 1  -->  1
     * 1  2     4 8  -->  15
     *       0 0 0         0  -->  0
     */
    int processaLinha(const std::string &str, Partida* Principal) override;
};

/**
 * \class LeitorDeFutebol
 *
 * Esta classe le uma sequencia de resultados de jogos de futebol, e imprime o
 * vencedor de cada partida.
 */
class espJogada: public LineProcessor {

  public:

    /**
     * Linhas validas contem quatro campos: "time1 gols1 time2 gols2". Time1 e
     * time2 sao nomes de times (palavras somente com letras, sem espacos ou
     * caracteres especiais). Gols1 e gols2 sao numeros naturais, isto eh,
     * inteiros positivos (sem o sinal de adicao).
     *
     * Exemplos de linhas validas:
     * America 2000 Atletico 1
     * Cruzeiro 42 Atletico 3
     * VilaChurupitaFC 0 GalaoDasMacas 0
     *
     * Exemplos de linhas invalidas:
     * Sao Paulo 0 GalaoDasMacas 0   // (note o espaco entre Sao e Paulo)
     * Sao_Paulo 0 Galao 0           // (note o sublinha)
     */
    bool linhaValida(const std::string &str) const override;

    /**
     * Para cada linha, deve-se imprimir o time vencedor, ou a palavra
     * 'Empate' no caso de placar igual. Quando houver time vencedor, o nome
     * do time deve ser precedido pela palavra "Vencedor: ". Note o espaco.
     * Exemplos:
     *
     * America 2000 Atletico 1  -->  Vencedor: America
     * Cruzeiro 42 Atletico 3  -->  Vencedor: Cruzeiro
     * VilaChurupitaFC 0 GalaoDasMacas 0  -->  Empate
     */
    int processaLinha(const std::string &str, Partida* Principal) override;
};
#endif