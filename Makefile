all : trab

run : 
	./trab
	
main.o: main.c
	gcc -o main.o -c main.c

mensagens.o: mensagens.c
	gcc -o mensagens.o -c mensagens.c

arquivos.o: arquivos.c
	gcc -o arquivos.o -c arquivos.c

trab : main.o arquivos.o mensagens.o 
	gcc -o trab main.o arquivos.o mensagens.o