// Problema B. h
#ifndef PROBLEMAB_H
#define PROBLEMAB_H

typedef FILE* ArqEntradaTipo;

// funções
void OrdeneExternoB();
void salvaArquivo(char *nome, TipoItem *V, TipoIndice n, TipoIndice limite, int mudaLinhaFinal);
int criaArquivosOrdenados(char *nomeArqEntrada, long int m);
int Minimo(int Lim, int High);
void AbreArqEntrada(ArqEntradaTipo* ArrArqEnt, int Low, int Lim);
ArqEntradaTipo AbreArqSaida(int NBlocos);
int retornaMenor(long int *chaves, long int n, ArqEntradaTipo ArqSaida);
long int retornaProximaChave(ArqEntradaTipo arq, long int count);
long int retornaTamanho(ArqEntradaTipo arq);
int isCountIgualALimite(long int *count, long int *limite, long int n);
void Apague_Arquivo(int numeroArq);
void Intercale(ArqEntradaTipo* ArrArqEnt, int Low, int Lim, ArqEntradaTipo ArqSaida);
// void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
// void Constroi(TipoItem *A, TipoIndice n);
// void Heapsort(TipoItem *A, TipoIndice n);
void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A);
void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void QuickSort(TipoItem *A, TipoIndice n);
void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void Constroi(TipoItem *A, TipoIndice n);
void Heapsort(TipoItem *A, TipoIndice n);

void OrdeneVetor(long int n,long int m, int OrdemIntercalConst, char *nomeArqEntrada);

#endif
