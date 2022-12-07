CC := g++
DEBUGFLAGS := -g3 -Wall -Werror
CFLAGS := -std=c++11 -o3 -march=native $(DEBUGFLAGS)

BIN := ./bin
HEADERS := ./headers
SRC := ./src

all: trab

trab: $(BIN) ALLBIN
	$(CC) $(CFLAGS) -o programaTrab $(BIN)/*.o
	
run:
	./programaTrab

clear: 
	rm $(BIN)/*.o

valgrind: trab
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./programaTrab

##__./bin_Directory__
$(BIN):
	mkdir -p $(BIN)
##--------------------	

##__$(BIN)/*.o_Files__
 
ALLBIN: $(BIN)/aresta.o $(BIN)/arquivoBin.o $(BIN)/arquivoCsv.o $(BIN)/arvoreB.o $(BIN)/cabecalhoArvB.o $(BIN)/funcionalidades.o $(BIN)/funcoesFornecidas.o $(BIN)/grafo.o $(BIN)/main.o $(BIN)/mensagens.o $(BIN)/noArvB.o $(BIN)/registroCabecalho.o $(BIN)/registroDados.o $(BIN)/registroDados.o $(BIN)/vertice.o

$(BIN)/main.o: $(SRC)/main.cpp
	$(CC) $(FLAGS) -o $(BIN)/main.o -c $(SRC)/main.cpp

$(BIN)/aresta.o: $(SRC)/aresta.cpp
	$(CC) $(FLAGS) -o $(BIN)/aresta.o -c $(SRC)/aresta.cpp

$(BIN)/arquivoBin.o: $(SRC)/arquivoBin.c
	$(CC) $(FLAGS) -o $(BIN)/arquivoBin.o -c $(SRC)/arquivoBin.c

$(BIN)/arquivoCsv.o: $(SRC)/arquivoCsv.c
	$(CC) $(FLAGS) -o $(BIN)/arquivoCsv.o -c $(SRC)/arquivoCsv.c

$(BIN)/arvoreB.o: $(SRC)/arvoreB.c
	$(CC) $(FLAGS) -o $(BIN)/arvoreB.o -c $(SRC)/arvoreB.c

$(BIN)/cabecalhoArvB.o: $(SRC)/cabecalhoArvB.c
	$(CC) $(FLAGS) -o $(BIN)/cabecalhoArvB.o -c $(SRC)/cabecalhoArvB.c

$(BIN)/funcionalidades.o: $(SRC)/funcionalidades.cpp
	$(CC) $(FLAGS) -o $(BIN)/funcionalidades.o -c $(SRC)/funcionalidades.cpp

$(BIN)/funcoesFornecidas.o: $(SRC)/funcoesFornecidas.c
	$(CC) $(FLAGS) -o $(BIN)/funcoesFornecidas.o -c $(SRC)/funcoesFornecidas.c	

$(BIN)/grafo.o: $(SRC)/grafo.cpp
	$(CC) $(FLAGS) -o $(BIN)/grafo.o -c $(SRC)/grafo.cpp

$(BIN)/mensagens.o: $(SRC)/mensagens.c
	$(CC) $(FLAGS) -o $(BIN)/mensagens.o -c $(SRC)/mensagens.c

$(BIN)/noArvB.o: $(SRC)/noArvB.c
	$(CC) $(FLAGS) -o $(BIN)/noArvB.o -c $(SRC)/noArvB.c

$(BIN)/registroCabecalho.o: $(SRC)/registroCabecalho.c
	$(CC) $(FLAGS) -o $(BIN)/registroCabecalho.o -c $(SRC)/registroCabecalho.c

$(BIN)/registroDados.o: $(SRC)/registroDados.c
	$(CC) $(FLAGS) -o $(BIN)/registroDados.o -c $(SRC)/registroDados.c

$(BIN)/vertice.o: $(SRC)/vertice.cpp
	$(CC) $(FLAGS) -o $(BIN)/vertice.o -c $(SRC)/vertice.cpp

##--------------------