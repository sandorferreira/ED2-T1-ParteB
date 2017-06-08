// Teste Segunda Parte
#include "criaArqAleatorio.h"
#include "problemaB.h"

// FUNÇÃO PARA CRIAR ARQUIVOS PSEUDOALEATÓRIOS: 
// --- criaArquivoAleatorio(long int tamanho, char* nome);

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i = Esq;
  long int j;
  TipoItem x;
  j = i * 2;
  x = A[i];
  while (j <= Dir) 
    { if (j < Dir) 
      { if (A[j].Chave < A[j+1].Chave) {
        j++;
        }

      }

      if (x.Chave >= A[j].Chave) goto L999;
      A[i] = A[j];
      i = j;  j = i * 2;
    }
  L999: A[i] = x; //mov += 2;
}

void Constroi(TipoItem *A, TipoIndice n)
{ TipoIndice Esq;
  Esq = n / 2 + 1;
  while (Esq > 1) 
    { Esq--;
      Refaz(Esq, n, A);
    }
}

/*--Entra aqui a funcao Refaz do Programa 4.9 --*/
/*--Entra aqui a funcao Constroi do Programa 4.10--*/

void Heapsort(TipoItem *A, TipoIndice n)
{ TipoIndice Esq, Dir;
  TipoItem x;
  Constroi(A, n);  /* constroi o heap */
  Esq = 1;  Dir = n;
  while (Dir > 1) 
    { /* ordena o vetor */
      x = A[1];  A[1] = A[Dir];  A[Dir] = x;  Dir--; //mov += 3; 
      Refaz(Esq, Dir, A);
    }
}

// Quick Sort

void Particao(TipoIndice Esq, TipoIndice Dir, 
              TipoIndice *i, TipoIndice *j, TipoItem *A)
{ TipoItem x, w;
  *i = Esq;  *j = Dir;
  x = A[(*i + *j) / 2]; //mov++; /* obtem o pivo x */
  do 
    { while (x.Chave > A[*i].Chave) {(*i)++; }
      while (x.Chave < A[*j].Chave) {(*j)--; }
      
      if (*i <= *j) 
      { w = A[*i]; A[*i] = A[*j]; A[*j] = w;
        //mov+=3;
        (*i)++; (*j)--;
      }
    } while (*i <= *j);
}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i, j;
  Particao(Esq, Dir, &i, &j, A);
  if (Esq < j) Ordena(Esq, j, A);
  if (i < Dir) Ordena(i, Dir, A);
}

void QuickSort(TipoItem *A, TipoIndice n)
{ Ordena(0, n-1, A); }

// se cabem apenas 3 registros na memória e se possui 3 fitas. Esses 3 registros ( se completos ) 
// geram na próxima fita 9 registros por intercalação.

void salvaArquivo(char *nome, TipoItem *V, TipoIndice n) {
	FILE *f = fopen(nome, "wb");
	//fwrite(&V->Chave, sizeof(long int), n - 1, f);

	for(i = 0; i < n ; i++) {
		long int chave = V[i].Chave;
		fwrite(&chave, sizeof(long int), 1, f);
	}

	fclose(f);
}

int criaArquivosOrdenados(char *nomeArqEntrada, long int m) {
	long int registros = m; long int total = 0; int count = 0;
	//long int V[registros]; 
	long int chave;
	TipoItem *Vaux;
	Vaux = (TipoItem *) malloc((registros+1) * sizeof(TipoItem));
	char novo[20];
	ArqEntradaTipo ArqEntrada = fopen(nomeArqEntrada, "rb");

	while(fread(&chave, sizeof(long int), 1, ArqEntrada) == 1) {
		TipoItem aux; aux.Chave = chave; strcpy(aux.Peso,"12345678901234567890123"); //puts(aux.Peso);
		Vaux[total] = aux;
		total++;
		if (total == registros) {
			count++;
			sprintf(novo, "Temp%d.bin", count);
			QuickSort(Vaux, total);
			salvaArquivo(novo, Vaux, total);
			total = 0; chave = 0;
		}
	}

	if (total > 0) {
		count ++;
		sprintf(novo, "Temp%d.bin", count);
		QuickSort(Vaux, total);
		salvaArquivo(novo, Vaux, total);
	}
	//printf("%d", count);

	fclose(ArqEntrada); free(Vaux);
	return count;
}



int Minimo(int Lim, int High) {
    if (High <= Lim) {
        return High;
    } else {
        return Lim;
    }
}

void AbreArqEntrada(ArqEntradaTipo* ArrArqEnt, int Low, int Lim) {
    char aux[30];
    for (int i = 0; i <= (Lim - Low); i++) {
        sprintf(aux, "Temp%d.bin", (Low + i + 1));
        ArrArqEnt[i] = fopen(aux, "rb");
    }
}

ArqEntradaTipo AbreArqSaida(int NBlocos) {
    char aux[30];
    sprintf(aux, "Temp%d.bin", NBlocos+1);
    //printf("abrindo arquivo High Temp%d.bin", NBlocos + 1);
    ArqEntradaTipo saida = fopen(aux, "wb");
    return saida;
}

int retornaMenor(long int *chaves,long int n, ArqEntradaTipo ArqSaida) {
	long int menor = chaves[0]; long int indice = 0;
	for (i = 0; i < n; i++) {
		if(menor == 0) {
			menor = chaves[i+1];
		}
		if (chaves[i] <= menor && chaves[i] != 0) {
			menor = chaves[i];
			indice = i;
		}
	}

	//printf("escrevendo MENOR: %li\n", menor);
	fwrite(&menor, sizeof(long int), 1, ArqSaida);
	return indice;
}

long int retornaProximaChave(ArqEntradaTipo arq, long int indice) {
	long int chave;
	fseek(arq, indice*sizeof(long int), SEEK_SET);
	if(fread(&chave, sizeof(long int), 1, arq) == 1) {
		return chave;
	} else {
		return 0;
	}
}

// long int retornaTamanho(ArqEntradaTipo arq) {
// 	long int count = 0;
// 	while (!feof(arq)) {
// 		count++;
// 	}
// 	fclose(arq);
// 	return count;
// }

int chegouAoFim(long int *chaves, long int n) {
	int aux = 0;
	for(i=0;i<n;i++) {
		if (chaves[i] == 0) {
			aux = aux + 1;
		}
	}

	if (aux >= n) {
		return 1;
	} else {
		return 0;
	}
}

void Apague_Arquivo(int numeroArq) {
    char aux[30];
    sprintf(aux, "Temp%d.bin", numeroArq+1); //printf("apagou arquivo Temp%d.bin\n", numeroArq+1);
    remove(aux);
}

void Intercale(ArqEntradaTipo* ArrArqEnt, int Low, int Lim, ArqEntradaTipo ArqSaida) {
	 int n = Lim - Low + 1; //printf("%d imprimindo N aqui", n);
	 long int *chaves;// = NULL;
	 long int *posicao; long int indice;//long int limite[n]; //long int indice = 0;
	 int fim = 0;

	 chaves = (long int *) malloc(n*sizeof(long int));
	 posicao = (long int *) malloc(n*sizeof(long int));

	 for(i=0;i< n;i++) {
	 	posicao[i] = 0;
	 	long int auxLI;
	 	if(fread(&auxLI, sizeof(long int), 1, ArrArqEnt[i])==1) {
	 		chaves[i] = auxLI;
	 		//printf("leu a chave %li\n", auxLI);
	 	}
	 }

	 while(fim == 0) {
	 	fim++;
	 	indice = retornaMenor(chaves, n, ArqSaida); //printf("%li indice\n", indice); 
		posicao[indice]++; // printf("posicao: %li -- deveria ser 2\n", posicao[indice]);
		chaves[indice] = retornaProximaChave(ArrArqEnt[indice], posicao[indice]); //printf("%li proxima chave hehe\n", chaves[indice]);
		for(i=0;i<n;i++) {
			//printf("%li\n", chaves[i]);
		}

		fim = chegouAoFim(chaves, n); //= isCountIgualALimite(posicao, limite, n); printf("%d FIM??",fim);
	 }

	 	free(chaves); free(posicao);

	 	fclose(ArqSaida);
	 	for(i=0;i<n;i++) {
	 		fclose(ArrArqEnt[i]);
	 		//Apague_Arquivo(i);
	 	}
	 	for(i=Low;i<Lim;i++) {
	 		Apague_Arquivo(i);
	 	}
	
}

void OrdeneVetor(long int m, int OrdemIntercalConst, char *nomeArqEntrada, char *nomeSaida) {
	int NBlocos = 0;
  	ArqEntradaTipo ArqSaida; // Arquivo de entrada é aberto pelo nome
		ArqEntradaTipo ArrArqEnt[OrdemIntercalConst];
		int Low, High, Lim;
		NBlocos = 0;
		NBlocos = criaArquivosOrdenados(nomeArqEntrada, m);
		Low = 0;
		High = NBlocos-1;

		while (Low < High) /* Intercalacao dos NBlocos ordenados */
		    { Lim = Minimo(Low + (OrdemIntercalConst-1), High);
		      AbreArqEntrada(ArrArqEnt, Low, Lim);
		      High++;
		      ArqSaida = AbreArqSaida(High);
		      Intercale(ArrArqEnt, Low, Lim, ArqSaida);
		      Low = Low + OrdemIntercalConst;
		    }
		    char aux[30];
		    sprintf(aux, "Temp%d.bin", High+1);
		    if(rename(aux, nomeSaida) == 0) {
		    	printf("\nArquivo de saida %s gerado.\n", nomeSaida);
		    } else {
		    	printf("\nArquivo de saida %s gerado\n", aux);
		    }
		    printf("\n\nCalculando tempo...\n");

		    for(i=0;i<m;i++) {
		    	Apague_Arquivo(i);
		    }
}

int main() {
	//OrdeneExternoB();
	long int n; int f; long int m;
	int aux1, aux2, aux3; char auxnomearqsaida[100];
	printf("--------------------------------------------------------\n");
	printf("----------------- TRABALHO 1 / PARTE 2 -----------------\n");
	printf("------------------ @ Sandor Ferreira -------------------\n");
	printf("--------------------------------------------------------\n\n");


	printf("Digite o valor de n:\n1: nˆ20\n2: nˆ21\n3: nˆ22\n\n");
	scanf("%d", &aux1);
	printf("\nDigite a Ordem de Intercalacao (f):\n1: f = 2\n2: f = 3\n3: f = 4\n");
	scanf("%d", &aux2);
	printf("\nDigite o valor de m (registros na memoria)\n1: m = n/4\n2: m = n/16\n3: m = n/256\n");
	scanf("%d", &aux3);
	printf("\nDigite o nome do arquivo de saida:\n");
	scanf("%s", auxnomearqsaida);
	printf("\n\n");

	//long int n, m;

	long int n1 = 1048576;
	long int n2 = 2097152;
	long int n3 = 4194304;
	long int auxN[3] = {n1, n2, n3};
	char nomes[3][30] = {"primeiro_arquivo_1.bin", "primeiro_arquivo_2.bin","primeiro_arquivo_3.bin"};
	char *nomeArq;

	n = auxN[aux1-1]; nomeArq = nomes[aux1-1];
	f = aux2+1;
	if(aux3 == 1) {
		m = n / 4;
	}

	if(aux3 == 2) {
		m = n / 16;
	}

	if(aux3 == 3) {
		m = n / 256;
	}

	tamBlocos = m;

	struct timeval inicio, final;
	double tMiliSec;

	printf("Criando arquivo aleatorio...");
	criaArquivoAleatorio(n, nomeArq);

	gettimeofday(&inicio, NULL);
	OrdeneVetor(m, f, nomeArq, auxnomearqsaida);
	gettimeofday(&final, NULL);
	tMiliSec = ((final.tv_sec * 1000 + final.tv_usec/1000) - (inicio.tv_sec * 1000 + inicio.tv_usec/1000));
	
	//tMiliSec = ((final.tv_sec * 1000 + final.tv_usec/1000) - (inicio.tv_sec * 1000000 + inicio.tv_usec/1000));
	printf("Tempo: %f  mili segundos\n", tMiliSec);

	return 0;
}
