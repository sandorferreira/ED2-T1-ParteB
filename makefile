#Para escrever comentários ##
############################# Makefile ##########################
all: teste
teste: criaArqAleatorio.o problemaB.o 
        # O compilador faz a ligação entre os dois objetos
		gcc -o teste criaArqAleatorio.o problemaB.o
#-----> Distancia com o botão TAB ### e não com espaços
teste.o: criaArqAleatorio.c
		gcc -o criaArqAleatorio.o -c criaArqAleatorio.c -W -g -Wall -pedantic
problemaB.o: problemaB.c criaArqAleatorio.h
		gcc -o problemaB.o -c problemaB.c -W -g -Wall -pedantic
clean:
		rm -rf *.o
mrproper: clean
		rm -rf teste
run: teste
	./teste