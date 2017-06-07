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
{ Ordena(0, n-1, A); }

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
		//printf("%li ", chave);
		//fscanf(ArqEntrada, "%li", &chave);
		//V[total] = chave;
		TipoItem aux; aux.Chave = chave; strcpy(aux.Peso,"12345678901234567890123"); //puts(aux.Peso);
		Vaux[total] = aux;
		total++;
		if (total == registros) {
			for(long int seila = 0; seila < total; seila++) {
				//Vaux[seila] = Vaux[seila + 1];
				printf("%li ", Vaux[seila].Chave);
				
			}
			printf("\n");
			printf("AGORA QUICKSORT --\n");
			count++;
			sprintf(novo, "Temp%d.bin", count);
			QuickSort(Vaux, total);
			for(long int seila = 0; seila < total; seila++) {
				//Vaux[seila] = Vaux[seila + 1];
				printf("%li ", Vaux[seila].Chave);
				
			}
			printf("\n");
			//printf("aaaaaaaa\n");
			//for(long int seila=1;seila<total;seila++){
				//printf("%li\n", Vaux[seila].Chave);
			//}
			salvaArquivo(novo, Vaux, total, registros, 0);
			total = 0; chave = 0;
		}
	}

	if (total > 0) {
		count ++;
		sprintf(novo, "Temp%d.bin", count);
		QuickSort(Vaux, total);
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
    char aux[30]; long int auxChave;
    printf("%d Lim - Low", (Lim - Low));
    for (int i = 0; i <= (Lim - Low); i++) {
        sprintf(aux, "Temp%d.bin", (Low + i + 1));
        ArrArqEnt[i] = fopen(aux, "rb");
        // if(fread(&auxChave, sizeof(long int), 1, ArrArqEnt[i])==1) {
        // 	printf("%li -- chave\n", auxChave);
        // }
    }
}

ArqEntradaTipo AbreArqSaida(int NBlocos) {
    char aux[30];
    sprintf(aux, "Temp%d.bin", NBlocos+1);
    printf("abrindo arquivo High Temp%d.bin", NBlocos + 1);
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

	printf("escrevendo MENOR: %li\n\n", menor);
	fwrite(&menor, sizeof(long int), 1, ArqSaida);
	return indice;

	// long int indice2 = 0; long int auxCount = 0;
	// for(i=0;i<n;i++) {
	// 	if(chaves[i] == 0) {
	// 		auxCount++;
	// 	} else {
	// 		indice2 = i;
	// 	}
	// }

	// if((auxCount == n-1)) {
	// 	menor = chaves[indice2];
	// 	if(menor != 0 ){
	// 		printf("escrevendo MENOR: %li\n\n", menor);
	// 		fwrite(&menor, sizeof(long int), 1, ArqSaida);
	// 	}
	// 	return indice2;
	// } else {

	// }

	// if(menor != 0 ){
	// 	printf("escrevendo MENOR: %li\n\n", menor);
	// 	fwrite(&menor, sizeof(long int), 1, ArqSaida);
	// }
	// //fprintf(ArqSaida, "%li ", menor);
	// return indice;
}

long int retornaProximaChave(ArqEntradaTipo arq, long int indice) {
	long int aux = 0; long int chave;
	fseek(arq, indice*sizeof(long int), SEEK_SET);
	if(fread(&chave, sizeof(long int), 1, arq) == 1) {
		return chave;
	} else {
		return 0;
	}

	// for(i=0;i<=indice;i++) {
	// 	if(fread(&chave, sizeof(long int), 1, arq) == 1) {
	// 		printf("\n%li -- proxima chave\n", chave);
	// 	} else {
	// 		return 0;
	// 	}
	// }

	// printf("\n%li -- proxima chave\n", chave);
	// return chave;

	// while(aux <indice) {
	// 	if (fread(&chave, sizeof(long int), 1, arq) != 1) {
	// 		if(aux >=10 && aux < 15 && !(feof(arq))) {
	// 			fread(&chave, sizeof(long int), 1, arq);
	// 		} else {
	// 			return 0;
	// 		}
	// 	} 
	// 	aux++;
	// }
	// printf("\n%li -- proxima chave\n", chave);
	// return chave;
}

long int retornaTamanho(ArqEntradaTipo arq) {
	long int count = 0;
	long int chave;
	while (!feof(arq)) {
		count++;
	}
	fclose(arq);
	return count;
}

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

// int isCountIgualALimite(long int *count, long int *limite, long int n) {
// 	int aux = 0;
// 	for (int i = 0; i < n; i ++) {
// 		if (count[i] == limite[i]) {
// 			aux++;
// 		}
// 	}

// 	if (aux == n) {
// 		return -1;
// 	} else {
// 		return 0;
// 	}
// }

void Apague_Arquivo(int numeroArq) {
    char aux[30];
    sprintf(aux, "Temp%d.bin", numeroArq+1); printf("apagou arquivo Temp%d.bin\n", numeroArq+1);
    remove(aux);
}

void Intercale(ArqEntradaTipo* ArrArqEnt, int Low, int Lim, ArqEntradaTipo ArqSaida, long int m) {
	 int n = Lim - Low + 1; printf("%d imprimindo N aqui", n);
	 long int chaves[n];
	 long int posicao[n]; long int indice;//long int limite[n]; //long int indice = 0;
	 long int auxChave;
	 int auxInt, fim = 0;

	 for(i=0;i<n;i++) {
	 	chaves[i] = (long int *) malloc((tamBlocos+1) * sizeof(long int));
	 	posicao[i] = (long int *) malloc((tamBlocos+1) * sizeof(long int));
	 }

	 // long int vetorTodasChaves[n];
	 // for(i=0;i<n;i++) {
	 // 	vetorTodasChaves[i] = (long int *) malloc((tamBlocos+1) * sizeof(long int));
	 // }

	// long int *inter1;
	// inter1 = (long int *) malloc((tamBlocos+1) * sizeof(long int));
	// long int *inter2;
	// inter2 = (long int *) malloc((tamBlocos+1) * sizeof(long int));
	// long int *inter3;
	// inter3 = (long int *) malloc((tamBlocos+1) * sizeof(long int));
	// long int *inter4;
	// inter4 = (long int *) malloc((tamBlocos+1) * sizeof(long int));



	 for(i=0;i< n;i++) {
	 	posicao[i] = 0;
	 	long int auxLI;
	 	if(fread(&auxLI, sizeof(long int), 1, ArrArqEnt[i])==1) {
	 		chaves[i] = auxLI;
	 		printf("leu a chave %li\n", auxLI);
	 	}
	 }

	 while(fim == 0) {
	 	fim++;
	 	indice = retornaMenor(chaves, n, ArqSaida); printf("%li indice\n", indice); 
		posicao[indice]++; // printf("posicao: %li -- deveria ser 2\n", posicao[indice]);
		for(i=0;i<n;i++) {
			printf("posicao: %li, ", posicao[i]);
		}
		chaves[indice] = retornaProximaChave(ArrArqEnt[indice], posicao[indice]); printf("%li proxima chave hehe\n", chaves[indice]);
		for(i=0;i<n;i++) {
			printf("%li\n", chaves[i]);
		}

		fim = chegouAoFim(chaves, n); //= isCountIgualALimite(posicao, limite, n); printf("%d FIM??",fim);
	 }
	
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
		    { Lim = Minimo(Low + (OrdemIntercalConst-1), High);
		      AbreArqEntrada(ArrArqEnt, Low, Lim);
		      High++;
		      printf("%d Low e %d Lim e %d High --", Low, Lim, High);
		      ArqSaida = AbreArqSaida(High);
		      printf("FLAG 00\n");
		      Intercale(ArrArqEnt, Low, Lim, ArqSaida,m);
		      //if(Lim == High) {
		      	long int auxChave = 0;
		      	while(fread(&auxChave, sizeof(long int), 1, ArqSaida) == 1) {
		      		printf("%li ", auxChave);
		      	}
		      
		      fclose(ArqSaida);
		      for(i= Low; i < Lim; i++)
		        { fclose(ArrArqEnt[i]);
		          //Apague_Arquivo(i);
		        }
		      Low = Low + OrdemIntercalConst;
		    }
		    // char velhoNome[30], novoNome[30];
    		// sprintf(velhoNome, "%d", High);
    		// int renomear = rename(velhoNome, "teste");
}

int main() {
	long int n = 2000000;
	long int m = n / 4; tamBlocos = m;
	criaArquivoAleatorio(n,"primeiro_arquivo.bin");
	int aha = criaArquivosOrdenados("primeiro_arquivo.bin", m);
	// for(i=1;i<5;i++) {
	// printf("arquivo %d ordenado??---\n", i);
	// long int chaveAux;
	// char nome[30];
	// sprintf(nome, "Temp%d.bin", i);
	// ArqEntradaTipo aarq = fopen(nome, "rb");
	// while(fread(&chaveAux, sizeof(long int), 1, aarq) ==1) {
	// 	printf("%li \n", chaveAux);
	// }
	// }
	printf("\n%d acabou\n", aha);
	OrdeneVetor(n, m, 3, "primeiro_arquivo.bin");

	for(i=1;i<7;i++) {
	printf("arquivo %d ordenado??---\n", i);
	long int chaveAux;
	char nome[30];
	sprintf(nome, "Temp%d.bin", i);
	ArqEntradaTipo aarq = fopen(nome, "rb");
	while(fread(&chaveAux, sizeof(long int), 1, aarq) ==1) {
		printf("%li \n", chaveAux);
	}
	}

	return 0;
}
