// #include   <limits.h>
// #include   <stdio.h>
// #include   <stdlib.h>
// #include   <string.h>
// #include   <sys/time.h>

//#define MAXTAM 100

#include "criaArqAleatorio.h"

// Gerador de números aleatórios

// Tipos 

//  --------------------------------------------
//	Criadores de arquivos com números aleatórios
//  -------------------------------------------- 


void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n)
{ for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}

double rand0a1() 
{ double resultado=  (double) rand()/ INT_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado= 1.0;
  return resultado;
}

void Permut( TipoItem *A, TipoIndice n) 
{ long int j;
  TipoItem b;

  for(i = n-1; i>0; i --) 
  { j = (i * rand0a1()) +1 ;
    b = A[i];
    A[i] = A[j];
    A[j] = b;
  }
}

void imprimeVetor(TipoItem *V, TipoIndice n) {
	for (i = 1; i <= n; i++)
    printf("%li ", V[i].Chave);  printf("\n");
}

void criaArquivoAleatorio(TipoIndice n, char *nomeArquivo) {
	//criaVetor(n);
	printf("tentando..\n");
	TipoItem *Aux;
	Aux = (TipoItem *) malloc((n+1) * sizeof(TipoItem));
	TipoItem *B;
	B = (TipoItem *) malloc((n+1) * sizeof(TipoItem));
	//long int auxCount = 0;
	for (i = 1; i <= n; i++) {
		TipoItem aux; aux.Chave = i; strcpy(aux.Peso, "12345678901234567890123");
		Aux[i] = aux;
	}
	
	Permut(Aux,n);
	Copia(Aux,B,n);
	
	// criando FILE
	FILE *fp;// = NULL;
	fp = fopen(nomeArquivo, "wb");
	if (fp != NULL) {
		//printf("\n FILE NOT NULL\n");
		for(i=1;i<=n;i++) {
			TipoChave chave = Aux[i].Chave;
			fwrite(&chave, sizeof(TipoChave), 1, fp);
		}
		fclose(fp);
	}
	free(Aux); free(B);
	//criaArquivoVetor(A,n,nomeArquivo);
}

