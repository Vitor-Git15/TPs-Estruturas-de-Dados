//---------------------------------------------------------------------
// Arquivo	: mat.cpp
// Conteudo	: implementacao do TAD MAT 
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-04-29 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "mat.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x,y) (x+=y,y=x-y,x-=y)
#define ELEMASS(mat, x, y, v) (mat->m[x][y] = v)

void criaMatriz(matriz_tipo * mat, int linhas, int cols, int id)
//Descrição: cria matriz com dimensões M[linhas][cols]
//Entrada: mat, linhas, cols, id
//Saída: mat
{
  // verifica se as dimensões da matriz são válidas
  erroAssert(linhas>1,"Dimensao da matriz inválida");
  erroAssert(cols>1,"Dimensao da matriz inválida");

  // inicializa as dimensões da matriz
  mat->linhas = linhas;
  mat->cols = cols;

  //inicializa o id da matriz (rastreamento)
  mat->id = id;

  //aloca matriz
  mat->m = new double *[mat->linhas];
  for(int i = 0; i < mat->linhas; i++){
    mat->m[i] = new double[mat->cols];
  }
  //verifica se a alocação ocorreu corretamente
  erroAssert(mat->m!=NULL,"Malloc falhou");
}

void inicializaMatrizNula(matriz_tipo * mat)
//Descrição: inicializa matriz com valores nulos
//Entrada: mat
//Saída: mat
{
  for (int i=0; i<mat->linhas; i++){    
    for (int j=0; j<mat->cols; j++){
      mat->m[i][j] = 0;
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
}
void inicializaMatriz(matriz_tipo * mat, std::string nome_arq)
// Descricao: inicializa mat com valores aleatorios
// Entrada: mat 
// Saida: mat
{
  // verifica se a matriz e o arquivo sao validos
  std::ifstream arq(nome_arq);
  erroAssert(arq, "Arquivo de matriz inexistente ou invalido.");

  // variavel auxiliar
  char aux;

  // preparacao para ler linha a linha
  std::string str;
  getline(arq, str);
  std::istringstream istr(str);

  inicializaMatrizNula(mat);

  // lendo e validando tamanho da matriz
  istr >> mat->linhas >> mat->cols;
  erroAssert(mat->linhas > 1 && mat->cols > 1, "Dimensao de matriz invalido.");

  // validando linha: nao pode ter nada alem desses dois numeros
  istr >> aux;
  erroAssert(istr.eof(), "Arquivo de matriz nao segue a especificacao.");
  double v;
  for (int i = 0; i < mat->linhas; i++)
  {
    // pegando proxima linha e colocando na stringstream
    getline(arq, str);
    istr.str(str);
    istr.clear();
    for(int j = 0; j < mat->cols; j++)
    {
      // validando a leitura do numero real
 
      //erroAssert(istr >> v && (istr.good() || istr.eof()), "Arquivo de matriz nao segue a especificacao.");
      istr >> v;
      ELEMASS(mat, i, j, v);
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }

    // validando final da linha: nao pode ter nada alem dos ty numeros
    istr >> aux;
    erroAssert(istr.eof(), "Arquivo de matriz nao segue a especificacao.");
  }
}

double acessaMatriz(matriz_tipo * mat)
// Descrição: acessa matriz para fins de registro de acesso
// Entrada: mat
// Saída: 
{
  double soma_aux;
  soma_aux = 0.0;
  for (int i=0; i<mat->linhas; i++){    
    for (int j=0; j<mat->cols; j++){

      soma_aux += mat->m[i][j];
      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
  return soma_aux;
}
void imprimeMatriz(matriz_tipo * mat, std::string nome_arq)
// Descrição: imprime o vetor com a identificacao das posicoes
// Entrada: mat
// Saída: impressao na saida padrao

{
  std::fstream arq_out(nome_arq);
  arq_out.open(nome_arq, std::ios_base::out);

  erroAssert(arq_out.is_open() == 1, "Erro na abertura do arquivo de saída.");

  arq_out << mat->linhas << " " << mat->cols << std::endl;

  for (int i = 0; i < mat->linhas; i++)
  {
    for (int j = 0; j < mat->cols; j++){
      arq_out << mat->m[i][j] << " ";
      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
    arq_out << std::endl;
  }

}
void somaMatrizes(matriz_tipo * a, matriz_tipo * b, matriz_tipo * c)
// Descricao: soma das matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
  // verifica as dimensoes das matrizes
  erroAssert(a->linhas == b->linhas, "Dimensões incompatíveis");
  erroAssert(a->cols == b->cols ,"Dimensões incompatíveis");  

  inicializaMatrizNula(c);

  for (int i=0; i<a->linhas; i++){    
    for (int j=0; j<a->cols; j++){

      c->m[i][j] = a->m[i][j] + b->m[i][j];

      LEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      LEMEMLOG((long int)(&(b->m[i][j])),sizeof(double),b->id);
      ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
    }
  }
}
void multiplicaMatrizes(matriz_tipo *a, matriz_tipo *b, matriz_tipo *c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
  erroAssert(a->cols==b->linhas,"Dimensoes incompativeis");

  // realiza a multiplicacao de matrizes
  for (int i=0; i<c->linhas;i++){
    for (int j=0; j<c->cols;j++){
      for (int k=0; k<a->cols;k++){
        c->m[i][j] += a->m[i][k]*b->m[k][j];
        LEMEMLOG((long int)(&(a->m[i][k])),sizeof(double),a->id);
        LEMEMLOG((long int)(&(b->m[k][j])),sizeof(double),b->id);
        ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
      }
    }
  }

}

void transpoeMatriz(matriz_tipo* a, matriz_tipo* b)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{

  // faz a transposicao como se a matriz fosse quadrada
  for (int i=0; i<a->cols; i++){
    for(int j=0; j<a->linhas; j++){
      
      b->m[i][j] = a->m[j][i];
      LEMEMLOG((long int)(&(a->m[j][i])),sizeof(double),a->id);
      ESCREVEMEMLOG((long int)(&(b->m[i][j])),sizeof(double),b->id);
    }
  }
  // inverte as dimensoes da matriz transposta
}

void destroiMatriz(matriz_tipo *a)
// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
{
  // apenas um aviso se a matriz for destruida mais de uma vez
  avisoAssert(((a->linhas>0)&&(a->cols>0)),"Matriz já foi destruida");

  // torna as dimensoes invalidas
  for(int i = 0; i < a->linhas; i++){
    free(a->m[i]);
  }
  free(a->m);

  a->id = a->linhas = a->cols = -1;

}
