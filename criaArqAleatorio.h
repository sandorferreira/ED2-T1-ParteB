#ifndef CRIAARQALEATORIO_H
#define CRIAARQALEATORIO_H

#include   <limits.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <sys/time.h>

typedef long int TipoChave;
typedef char TipoPeso[24];
typedef struct TipoItem {
  TipoChave Chave;
  TipoPeso Peso;

} TipoItem;

typedef long int TipoIndice;
long int i, n, tamBlocos;
int ordemIntercalAux;

//  --------------------------------------------
//	Funções auxiliares para desordenar valores
//  -------------------------------------------- 

void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n);
double rand0a1();
void Permut( TipoItem *A, TipoIndice n) ;
void imprimeVetor(TipoItem *V, TipoIndice n);

//  -------------------------------------------------------------------
//	Função que cria arquivo de qualquer tamanho n de números aleatórios
//  -------------------------------------------------------------------

void criaArquivoAleatorio(TipoIndice n, char *nomeArquivo);

#endif
