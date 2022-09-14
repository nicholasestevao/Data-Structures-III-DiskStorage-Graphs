all : trab

run : 
	./trab
	
main.o: main.c
	gcc -o main.o -c main.c

mensagens.o: mensagens.c
	gcc -o mensagens.o -c mensagens.c

arquivos.o: arquivos.c
	gcc -o arquivos.o -c arquivos.c

registros.o: registros.c
	gcc -o registros.o -c registros.c

trab : main.o arquivos.o mensagens.o registros.o
	gcc -o trab main.o arquivos.o mensagens.o registros.o