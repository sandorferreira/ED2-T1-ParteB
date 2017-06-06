#ifndef PROBLEMAA_H
#define PROBLEMAA_H

struct registroA {
    char chave;
    char peso[32];
};

typedef FILE* ArqEntradaTipo;
typedef struct registroA TipoRegistroA;

void OrdeneExternoA();
short EnchePaginas(int m, int NBlocos, ArqEntradaTipo ArqEntrada, TipoRegistroA* memoria);
void OrdeneInterno(int m, int ordem[], TipoRegistroA* memoria);
ArqEntradaTipo AbreArqSaida(int NBlocos);
void DescarregaPaginas(int m, int ordem[], ArqEntradaTipo ArqSaida, TipoRegistroA* memoria);
int Minimo(int Lim, int High);
void AbreArqEntrada(ArqEntradaTipo* ArrArqEnt, int Low, int Lim);
void Intercale(ArqEntradaTipo* ArrArqEnt, int Low, int Lim, ArqEntradaTipo ArqSaida);
void Apague_Arquivo(int numeroArq);
#endif /* PROBLEMAA_H */

