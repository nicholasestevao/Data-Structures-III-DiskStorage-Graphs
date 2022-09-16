all : trab

run : 
	./trab
	
./Obj/main.o: main.c
	gcc -o ./Obj/main.o -c main.c

./Obj/mensagens.o: ./C/mensagens.c
	gcc -o ./Obj/mensagens.o -c ./C/mensagens.c

./Obj/arquivos.o: ./C/arquivos.c
	gcc -o ./Obj/arquivos.o -c ./C/arquivos.c

./Obj/registros.o: ./C/registros.c
	gcc -o ./Obj/registros.o -c ./C/registros.c

./Obj/funcoesFornecidas.o: ./C/funcoesFornecidas.c
	gcc -o ./Obj/funcoesFornecidas.o -c ./C/funcoesFornecidas.c	

trab : ./Obj/main.o ./Obj/arquivos.o ./Obj/mensagens.o ./Obj/registros.o ./Obj/funcoesFornecidas.o
	gcc -o trab ./Obj/main.o ./Obj/arquivos.o ./Obj/mensagens.o ./Obj/registros.o ./Obj/funcoesFornecidas.o