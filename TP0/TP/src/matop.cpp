//---------------------------------------------------------------------
// Arquivo	: matop.cpp
// Conteudo	: implementacao do TAD MAT
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-04-29 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "mat.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

// definicoes de operacoes a serem testadas
#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3

// variaveis para opcoes
typedef struct opt{
  int opescolhida;
  std::string mat1, mat2, mat_result, lognome;
  int optx_mat1, opty_mat1, optx_mat2, opty_mat2;
  int regmem;
} opt_tipo;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr, "matop\n");
  fprintf(stderr, "\t-s \t(somar matrizes) \n");
  fprintf(stderr, "\t-m \t(multiplicar matrizes) \n");
  fprintf(stderr, "\t-t \t(transpor matriz)\n");
  fprintf(stderr, "\t-1 m1.txt\t(matriz 1)\n");
  fprintf(stderr, "\t-2 m2.txt\t(matriz 2)\n");
  fprintf(stderr, "\t-o res.out\t(matriz resultante)\n");
  fprintf(stderr, "\t-p log.out\t(registro de desempenho)\n");
  fprintf(stderr, "\t-l \t(padrão de acesso e localidade)\n");
}

void abreArquivo(std::string nome_arq, char c, opt_tipo * opt)
{
  std::ifstream arq(nome_arq);

  erroAssert(arq, "Problema na Criacao do arquivo");

  std::string str_aux;
  getline(arq, str_aux);
  std::istringstream istr(str_aux);

  if (c == '1')
  {
    istr >> opt->optx_mat1 >> opt->opty_mat1;
    erroAssert(opt->optx_mat1 > 1 && opt->opty_mat1 > 1, "Dimensoes de matriz invalida."); 

  } else if(c == '2'){

    istr >> opt->optx_mat2 >> opt->opty_mat2;
    erroAssert(opt->optx_mat2 > 1 && opt->opty_mat2 > 1, "Dimensoes de matriz invalida."); 

  } else{

    uso();
    exit(1);
  }
}

void parse_args(int argc, char **argv, opt_tipo * opt)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
{
  //
  erroAssert(argc > 1, "Poucos argumentos foram apresentados");

  // variaveis externas do getopt
  extern char *optarg;

  // inicializacao das variaveis para opcoes
  opt->opescolhida = -1;
  opt->optx_mat1 = -1;
  opt->opty_mat1 = -1;
  opt->optx_mat2 = -1;
  opt->opty_mat2 = -1;
  opt->regmem = 0;
  opt->mat1[0] = 0;
  opt->mat2[0] = 0;
  opt->mat_result[0] = 0;
  opt->lognome[0] = 0;

  // variavel auxiliar
  int c;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "smtp:1:2:lo:h")) != EOF)
    switch (c)
    {
    case 'm':
      avisoAssert(opt->opescolhida == -1, "Mais de uma operacao escolhida");
      opt->opescolhida = OPMULTIPLICAR;
      break;
    case 's':
      avisoAssert(opt->opescolhida == -1, "Mais de uma operacao escolhida");
      opt->opescolhida = OPSOMAR;
      break;
    case 't':
      avisoAssert(opt->opescolhida == -1, "Mais de uma operacao escolhida");
      opt->opescolhida = OPTRANSPOR;
      break;
    case '1':
      opt->mat1 = optarg;
      erroAssert(opt->mat1.length() > 0,
             "matop - nome de arquivo de registro de acesso tem que ser definido");
      abreArquivo(opt->mat1, c, opt);

      //verificacao da consistencia das dimencoes da matriz 1
      erroAssert(opt->optx_mat1 > 1, "matop - dimensao X da matriz tem que ser positiva");
      erroAssert(opt->opty_mat1 > 1, "matop - dimensao Y da matriz tem que ser positiva");
      break;
    case '2':
      opt->mat2 = optarg;
      erroAssert(opt->mat2.length() > 0,
             "matop - nome de arquivo de registro de acesso tem que ser definido");
      abreArquivo(opt->mat2, c, opt);
      //verificacao da consistencia das dimencoes da matriz 2
      erroAssert(opt->optx_mat2 > 1, "matop - dimensao X da matriz tem que ser positiva");
      erroAssert(opt->opty_mat2 > 1, "matop - dimensao Y da matriz tem que ser positiva");
      break;
    case 'o':
      opt->mat_result = optarg;
      break;
    case 'p':
      opt->lognome = optarg; 
      break;
    case 'l':
      opt->regmem = 1;
      break;
    case 'h':
    default:
      uso();
      exit(1);
    }

  // verificacao da consistencia das opcoes
  erroAssert(opt->opescolhida > 0, "matop - necessario escolher operacao");
}

int main(int argc, char **argv)
// Descricao: programa principal para execucao de operacoes de matrizes
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{
  // ate 3 matrizes sao utilizadas, dependendo da operacao
  matriz_tipo a, b, c;

  opt_tipo opt;

  // avaliar linha de comando
  parse_args(argc, argv, &opt);

  // iniciar registro de acesso
  char logoname[100];
  strcpy(logoname, opt.lognome.c_str());
  iniciaMemLog(logoname);

  // ativar ou nao o registro de acesso
  if (opt.regmem)
  {
    ativaMemLog();
  }
  else
  {
    desativaMemLog();
  }

  // execucao dependente da operacao escolhida
  switch (opt.opescolhida)
  {
  case OPSOMAR:
    // cria matrizes a e b aleatorias, que sao somadas para a matriz c
    // matriz c é impressa e todas as matrizes sao destruidas
    defineFaseMemLog(0);
      criaMatriz(&a, opt.optx_mat1, opt.opty_mat1, 0);
      inicializaMatriz(&a, opt.mat1);
      criaMatriz(&b, opt.optx_mat2, opt.opty_mat2, 1);
      inicializaMatriz(&b, opt.mat2);
      criaMatriz(&c, opt.optx_mat1, opt.opty_mat1, 2);
      inicializaMatrizNula(&c);
    defineFaseMemLog(1);
      acessaMatriz(&a);
      acessaMatriz(&b);
      acessaMatriz(&c);
      somaMatrizes(&a, &b, &c);
    defineFaseMemLog(2);
      acessaMatriz(&c);
      imprimeMatriz(&c, opt.mat_result);
      destroiMatriz(&a);
      destroiMatriz(&b);
      destroiMatriz(&c);
    break;
  case OPMULTIPLICAR:
    // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
    // matriz c é impressa e todas as matrizes sao destruidas
    defineFaseMemLog(0);
      criaMatriz(&a, opt.optx_mat1, opt.opty_mat1, 0);
      inicializaMatriz(&a, opt.mat1);
      criaMatriz(&b, opt.optx_mat2, opt.opty_mat2, 1);
      inicializaMatriz(&b, opt.mat2);
      criaMatriz(&c, opt.optx_mat1, opt.opty_mat2, 2);
      inicializaMatrizNula(&c);
    defineFaseMemLog(1);
      acessaMatriz(&a);
      acessaMatriz(&b);
      acessaMatriz(&c);
      multiplicaMatrizes(&a, &b, &c);
    defineFaseMemLog(2);
      acessaMatriz(&c);
      imprimeMatriz(&c, opt.mat_result);
      destroiMatriz(&a);
      destroiMatriz(&b);
      destroiMatriz(&c);
    break;
  case OPTRANSPOR:
    // cria matriz a aleatoria, que e transposta, impressa e destruida
    defineFaseMemLog(0);
      criaMatriz(&a, opt.optx_mat1, opt.opty_mat1, 0);
      inicializaMatriz(&a, opt.mat1);
      criaMatriz(&b, opt.opty_mat1, opt.optx_mat1, 1);
      inicializaMatrizNula(&b);
    defineFaseMemLog(1);
      acessaMatriz(&a);
      acessaMatriz(&b);
      transpoeMatriz(&a, &b);
    defineFaseMemLog(2);
      acessaMatriz(&b);
      imprimeMatriz(&b, opt.mat_result);
      destroiMatriz(&a);
      destroiMatriz(&b);
    break;
  default:
    // nao deve ser executado, pois ha um erroAssert em parse_args
    uso();
    exit(1);
  }

  // conclui registro de acesso
  return finalizaMemLog();
}
