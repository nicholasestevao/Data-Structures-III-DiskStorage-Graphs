all : trab

run : 
	./trab
	
./bin/main.o: ./src/main.c
	gcc -o ./bin/main.o -c ./src/main.c

./bin/mensagens.o: ./src/mensagens.c
	gcc -o ./bin/mensagens.o -c ./src/mensagens.c

./bin/arquivos.o: ./src/arquivos.c
	gcc -o ./bin/arquivos.o -c ./src/arquivos.c

./bin/registros.o: ./src/registros.c
	gcc -o ./bin/registros.o -c ./src/registros.c

./bin/funcoesFornecidas.o: ./src/funcoesFornecidas.c
	gcc -o ./bin/funcoesFornecidas.o -c ./src/funcoesFornecidas.c	

trab : ./bin/main.o ./bin/arquivos.o ./bin/mensagens.o ./bin/registros.o ./bin/funcoesFornecidas.o
	gcc -o trab ./bin/main.o ./bin/arquivos.o ./bin/mensagens.o ./bin/registros.o ./bin/funcoesFornecidas.o

rm: ./bin/*.o
	rm ./bin/*.o *.exe
