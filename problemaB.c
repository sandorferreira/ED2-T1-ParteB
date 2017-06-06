// Teste Segunda Parte
#import "criaArqAleatorio.h"
#import "problemaB.h"

void OrdeneExternoB() {


}

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
{ Ordena(1, n, A); }

// se cabem apenas 3 registros na memória e se possui 3 fitas. Esses 3 registros ( se completos ) 
// geram na próxima fita 9 registros por intercalação.

void salvaArquivo(char *nome, TipoItem *V, TipoIndice n, TipoIndice limite, int mudaLinhaFinal) {
	FILE *f = fopen(nome, "wb");
	//fwrite(&V->Chave, sizeof(long int), n - 1, f);

	for(i = 0; i < n ; i++) {
		long int chave = V[i].Chave;
		fwrite(&chave, sizeof(long int), 1, f);
	}

	fclose(f);
}

void verificaVetor(TipoItem *V, TipoIndice n) {
	TipoItem *Aux;
	for(int aux=1;i<=n;i++) {
		Aux[aux-1] = V[aux];
	}
	V = Aux;
}

int criaArquivosOrdenados(char *nomeArqEntrada, long int m) {
	long int registros = m; long int total = 0; long int count = 0;
	//long int V[registros]; 
	long int chave;
	TipoItem *Vaux;
	Vaux = (TipoItem *) malloc((registros+1) * sizeof(TipoItem));
	char novo[20];
	ArqEntradaTipo ArqEntrada = fopen(nomeArqEntrada, "rb");

	while(fread(&chave, sizeof(long int), 1, ArqEntrada) == 1) {
		//if(feof(ArqEntrada)){ break;}
		//fread(&chave, sizeof(long int), 1, ArqEntrada);
		printf("%li ", chave);
		//fscanf(ArqEntrada, "%li", &chave);
		//V[total] = chave;
		TipoItem aux; aux.Chave = chave; strcpy(aux.Peso,"12345678901234567890123"); //puts(aux.Peso);
		Vaux[total] = aux;
		total++;
		if (total == registros) {
			count++;
			sprintf(novo, "Temp%d.bin", count);
			QuickSort(Vaux, total);
			for(long int seila = 0; seila <= total; seila++) {
				//printf("%li\n", Vaux[seila].Chave);
				Vaux[seila] = Vaux[seila + 1];
			}
			//printf("aaaaaaaa\n");
			for(long int seila=1;seila<total;seila++){
				//printf("%li\n", Vaux[seila].Chave);
			}
			salvaArquivo(novo, Vaux, total, registros, 0);
			total = 0;
		}
	}

	if (total > 0) {
		count ++;
		sprintf(novo, "Temp%d.bin", count);
		QuickSort(Vaux, total - 1);
		salvaArquivo(novo, Vaux, total, registros, 0);
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
        sprintf(aux, "Temp%d.bin", (Low + i));
        ArrArqEnt[i] = fopen(aux, "r");
    }
}

ArqEntradaTipo AbreArqSaida(int NBlocos) {
    char aux[30];
    sprintf(aux, "Temp%d.bin", NBlocos);
    ArqEntradaTipo saida = fopen(aux, "wb");
    return saida;
}

int retornaMenor(long int *chaves,long int n, ArqEntradaTipo ArqSaida) {
	long int menor = chaves[0]; long int indice = 0;
	for (i = 0; i < n; i++) {
		if (chaves[i] < menor) {
			menor = chaves[i];
			indice = i;
		}
	}
	fprintf(ArqSaida, "%li ", menor);
	return indice;
}

long int retornaProximaChave(ArqEntradaTipo arq, long int count) {
	long int aux = 0; int fim = 0;
	while(!feof(arq) && fim == 0) {
		aux++;
		if(aux == count) {
			fscanf(arq, "%li", &aux);
			fim = 1;
		}
	}
	return aux;
}

long int retornaTamanho(ArqEntradaTipo arq) {
	long int count = 0;
	while (!feof(arq)) {
		count++;
	}
	return count;
}

int isCountIgualALimite(long int *count, long int *limite, long int n) {
	int aux = 0;
	for (int i = 0; i < n; i ++) {
		if (count[i] == limite[i]) {
			aux++;
		}
	}

	if (aux == n) {
		return -1;
	} else {
		return 0;
	}
}

void Apague_Arquivo(int numeroArq) {
    char aux[30];
    sprintf(aux, "Temp%d.bin", numeroArq);
    remove(aux);
}

void Intercale(ArqEntradaTipo* ArrArqEnt, int Low, int Lim, ArqEntradaTipo ArqSaida) {
	int n = Lim - Low + 1; int indice = 0;
	long int chaves[n];
	long int count[n]; long int limite[n];

	//inicializando todos os counts em 0
	for(int i = 0; i < n; i ++) {
		count[i] = 0;
		limite[i] = retornaTamanho(ArrArqEnt[i]);
	}

	int fim = 0;

	for(i = 0; i < (Lim - Low); i++) {
		long int auxLI;
		fscanf(ArrArqEnt[i], "%li", &auxLI); // pegando primeiro long int de cada arquivo
		chaves[i] = auxLI;
	}

	do {
		indice = retornaMenor(chaves, n, ArqSaida);
		count[indice]++;
		if (count[indice] != limite[indice] ) {
			chaves[indice] = retornaProximaChave(ArrArqEnt[indice], count[indice]);
		}

		fim = isCountIgualALimite(count, limite, n);

	} while (fim == 0);	
}


void OrdeneVetor(long int n, long int m, int OrdemIntercalConst, char *nomeArqEntrada) {
	int NBlocos = 0;
  	ArqEntradaTipo ArqEntrada, ArqSaida;
		ArqEntradaTipo ArrArqEnt[OrdemIntercalConst];
		int Low, High, Lim;
		NBlocos = 0;
		NBlocos = criaArquivosOrdenados(nomeArqEntrada, m);
		Low = 0;
		High = NBlocos-1;
		while (Low < High) /* Intercalacao dos NBlocos ordenados */
		    { Lim = Minimo(Low + OrdemIntercalConst-1, High);
		      AbreArqEntrada(ArrArqEnt, Low, Lim);
		      printf("FLAG 00\n");
		      High++;
		      ArqSaida = AbreArqSaida(High);
		      Intercale(ArrArqEnt, Low, Lim, ArqSaida);
		      fclose(ArqSaida);
		      for(i= Low; i < Lim; i++)
		        { fclose(ArrArqEnt[i]);
		          Apague_Arquivo(i);
		        }
		      Low += OrdemIntercalConst;
		    }
		    // char velhoNome[30], novoNome[30];
    		// sprintf(velhoNome, "%d", High);
    		// int renomear = rename(velhoNome, "teste");
}

int main() {
	long int n = 50;
	long int m = n / 4;
	criaArquivoAleatorio(n,"primeiro_arquivo.bin");
	int aha = criaArquivosOrdenados("primeiro_arquivo.bin", m);
	printf("\n%d acabou\n", aha);
	OrdeneVetor(n, m, 3, "primeiro_arquivo.bin");

	return 0;
}
