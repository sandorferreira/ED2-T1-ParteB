#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problemaA.h"

void OrdeneExternoA() {
    int m = 4; //QUANTIDADE DE REGISTROS NA MEMORIA
    int OrdemIntercalacao = 2; //QUANTIDADE DE ARQUIVOS PARA INTERCALAR
    int NBlocos = 0; //IMAGINO QUE SEJA O QUE VAI IDENTIFICAR OS BLOCOS;;
    int ordem[m];
    ArqEntradaTipo ArqEntrada, ArqSaida;
    ArqEntradaTipo ArrArqEnt[OrdemIntercalacao];
    TipoRegistroA memoria[m];
    ArqSaida = fopen("arquivosaida.bin", "w");
    short Fim;
    int Low, High, Lim;
    NBlocos = 0;
    ArqEntrada = fopen("arquivoentrada.txt", "r");
    do /*Formacao inicial dos NBlocos ordenados */ {
        Fim = EnchePaginas(m, NBlocos, ArqEntrada, memoria); //PEGA A QUANTIDADE DE REGISTROS NÃO USADOS
        m -= Fim; //LIMITE DE REGISTROS MENOS A QUANTIDADE NÃO USADA, PARA NÃO VERIFICAR REGISTROS QUE NÃO ESTÃO SENDO USADOS
        OrdeneInterno(m, ordem, memoria); //ORDENA OS REGISTROS
        ArqSaida = AbreArqSaida(NBlocos);
        DescarregaPaginas(m, ordem, ArqSaida, memoria);
        NBlocos++;
        fclose(ArqSaida);
    } while (!Fim);
    fclose(ArqEntrada);
    Low = 0;
    High = NBlocos - 1;
    printf("Low foi usado como valor do menor arquivo que não foi ordenado ainda."
            " Lim é até qual arquivo (a partir do Low), será ordernado dessa vez. "
            "High é o arquivo com a numeração mais alta já criado.\n\n");
    int counter = 1;
    while (Low < High) /* Intercalacao dos NBlocos ordenados */ {
        Lim = Minimo(Low + OrdemIntercalacao - 1, High);
        printf("%dª interação: Low = %d | Lim = %d | High = %d\n", counter, Low, Lim, High);
        AbreArqEntrada(ArrArqEnt, Low, Lim);
        High++;
        printf("Arquivo de saída: '%d': ", High);
        ArqSaida = AbreArqSaida(High);
        Intercale(ArrArqEnt, Low, Lim, ArqSaida);
        fclose(ArqSaida);
        for (int i = Low; i <= Lim; i++) {
            fclose(ArrArqEnt[Lim - i]);
            Apague_Arquivo(i);
        }
        Low += OrdemIntercalacao;
        counter++;
    }
    char velhoNome[30], novoNome[30];
    sprintf(velhoNome, "%d", High);
    int renomear = rename(velhoNome, "teste");
}

short EnchePaginas(int m, int NBlocos, ArqEntradaTipo ArqEntrada, TipoRegistroA* registro) {
    char aux;
    for (short i = 0; i < m; i++) {
        aux = fgetc(ArqEntrada);
        if (aux == '\n') {
            aux = fgetc(ArqEntrada);

        } else if (aux != EOF) {
            registro[i].chave = aux;
            strcpy(registro[i].peso, "1234567890123456789012345678901"); //STRING DE 31 CHARS
        } else {
            return (m - i + 1); //SE ALCANÇAR O FINAL DO ARQUIVO RETORNA A QUANTIDADE DE REGISTRO NA MEMORIA QUE NAO USOU

        }
        char aux = fgetc(ArqEntrada); //PARA TIRAR OS \n DEPOIS DE CADA LETRA
    }
    return 0; //SE NÃO ALCANÇAR, RETORNA 0 PARA CONTINUAR PEGANDO BLOCOS DEPOIS
}

void OrdeneInterno(int m, int ordem[], TipoRegistroA* memoria) {
    char auxChar;
    int usado, auxInt;

    for (int i = 0; i < m; i++) {
        ordem[i] = 999; //TODAS AS POSIÇÕES RECEBEM UM VALOR MAIS ALTO QUE A QUANTIDADE DE REGISTROS NA MEMORIA
    }

    for (int i = 0; i < m; i++) { //PASSA TODAS A POSIÇÕES DO VETOR DE ORDEM
        auxChar = 'Z';
        for (int j = 0; j < m; j++) { //PASSA POR TODAS OS REGISTROS NA MÉMORIA
            usado = 0;
            if (strcmp(&auxChar, &memoria[j].chave) >= 0) { //AS CHAVES COM VALOR MAIS BAIXO ENTRAM NESSE 'IF'
                for (int k = 0; k < m; k++) { //OUTRO PARA PASSAR PELAS POSIÇÕES DO VETOR DE ORDEM
                    if (ordem[k] == j) { //CASO O VETOR DE ORDEM JÁ TENHA ESSE REGISTRO, NAO SERA CONSIDERADO A CHAVE MAIS BAIXA
                        usado = 1;
                    }
                }
                if (usado == 0) { //CASO NÃO TENHA AINDA O REGISTRO NO VETOR DE ORDEM, ELE SE TORNA A CHAVE COM VALOR MAIS BAIXO
                    auxChar = memoria[j].chave;
                    auxInt = j;
                }
            }
        }
        ordem[i] = auxInt; //A CHAVE MAIS BAIXA ENTRA PARA O VETOR DE ORDEM
    } //NO FINAL O VETOR DE ORDEM FICA, POR EXEMPLO, "4132", SIGNIFICA QUE 4ºREGISTRO PRIMEIRO, 1ºREGISTRO EM SEGUNDO,ETC...
}

ArqEntradaTipo AbreArqSaida(int NBlocos) {
    char aux[30];
    sprintf(aux, "%d", NBlocos);
    ArqEntradaTipo saida = fopen(aux, "w");
    return saida;
}

void DescarregaPaginas(int m, int ordem[], ArqEntradaTipo ArqSaida, TipoRegistroA* memoria) {
    int aux;
    for (int i = 0; i < m; i++) {
        aux = ordem[i];
        fwrite(&memoria[aux].chave, sizeof (char), 1, ArqSaida);
        fwrite(&memoria[aux].peso, sizeof (char), 31, ArqSaida);
    }
}

int Minimo(int Lim, int High) {
    if (High <= Lim) {
        return High;
    } else {
        return Lim;
    }
}

void AbreArqEntrada(ArqEntradaTipo* ArrArqEnt, int Low, int Lim) {
    char aux[30], auxChar;
    for (int i = 0; i <= (Lim - Low); i++) {
        sprintf(aux, "%d", (Low + i));
        printf("Arquivo de entrada '%s': ", aux);
        ArrArqEnt[i] = fopen(aux, "r");
        while (1) {
            auxChar = fgetc(ArrArqEnt[i]);
            if (auxChar == EOF) {
                break;
            }
            else{
                printf("%c", auxChar);
                fread(&aux, sizeof(char),31,ArrArqEnt[i]);
            }
        }
        printf("\n");
        rewind(ArrArqEnt[i]);
    }
}

void Intercale(ArqEntradaTipo* ArrArqEnt, int Low, int Lim, ArqEntradaTipo ArqSaida) {
    char chaves[Lim - Low + 1];
    char auxChar, auxChar2;
    int auxInt, fim = 0;
    char auxString[40];
    for (int i = 0; i <= (Lim - Low); i++) {
        chaves[i] = fgetc(ArrArqEnt[i]);
    }
    while (fim != 1) {
        auxChar = 'Z';
        auxInt = 999;
        for (int i = 0; i <= (Lim - Low); i++) {
            if ((strcmp(&auxChar, &chaves[i]) > 0)&&(chaves[i] != EOF)) {
                auxChar = chaves[i];
                auxInt = i;
            }
        }
        if (auxInt != 999) {
            printf("%c", chaves[auxInt]);
            fwrite(&chaves[auxInt], sizeof (char), 1, ArqSaida);
            for (int i = 0; i < 31; i++) {
                auxChar2 = fgetc(ArrArqEnt[auxInt]);
                fwrite(&auxChar2, sizeof (char), 1, ArqSaida);
            }
            chaves[auxInt] = fgetc(ArrArqEnt[auxInt]);
        } else {
            fim = 1;
        }
    }
    printf("\n\n");
}

void Apague_Arquivo(int numeroArq) {
    char aux[30];
    sprintf(aux, "%d", numeroArq);
    remove(aux);
}