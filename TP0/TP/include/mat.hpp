//---------------------------------------------------------------------
// Arquivo	: mat.hpp
// Conteudo	: implementacao do TAD MAT 
// Autor	: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
// Historico	: 2022-04-29 - arquivo criado
//---------------------------------------------------------------------
#ifndef MATH
#define MATH

typedef struct matriz{
	double** m;
	int linhas, cols;
	int id;
} matriz_tipo;

void criaMatriz(matriz_tipo* mat, int linhas, int cols, int id);
void inicializaMatrizNula(matriz_tipo* mat);
void inicializaMatriz(matriz_tipo* mat, std::string nome_arq);
double acessaMatriz(matriz_tipo* mat);
void imprimeMatriz(matriz_tipo * mat, std::string nome_arq);
void escreveElemento(matriz_tipo* mat, int linha, int col, double v);
double leElemento (matriz_tipo* mat, int pos);
void copiaMatriz(matriz_tipo* src, matriz_tipo* dst, int dst_id);
void somaMatrizes(matriz_tipo* a, matriz_tipo* b, matriz_tipo* c);
void multiplicaMatrizes(matriz_tipo* a, matriz_tipo*b, matriz_tipo*c);
void transpoeMatriz(matriz_tipo* a, matriz_tipo* b);
void destroiMatriz(matriz_tipo* a);

#endif