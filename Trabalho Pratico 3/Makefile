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
	rm $(BIN)/*.o programaTrab programaTrab.exe  

valgrind: trab
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./programaTrab

##__./bin_Directory__
$(BIN):
	mkdir -p $(BIN)
##--------------------

##__$(BIN)/*.o_Files__
ALLBIN: $(BIN)/aresta.o $(BIN)/arquivoBin.o $(BIN)/arquivoCSV.o $(BIN)/arvoreB.o $(BIN)/cabecalhoArvB.o $(BIN)/funcionalidades.o $(BIN)/funcoesFornecidas.o $(BIN)/grafo.o $(BIN)/main.o $(BIN)/mensagens.o $(BIN)/noArvB.o $(BIN)/registroCabecalho.o $(BIN)/registroDados.o $(BIN)/registroDados.o $(BIN)/vertice.o

$(BIN)/main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(BIN)/main.o -c $(SRC)/main.cpp 

$(BIN)/aresta.o: $(SRC)/aresta.cpp
	$(CC) $(CFLAGS) -o $(BIN)/aresta.o -c $(SRC)/aresta.cpp

$(BIN)/arquivoBin.o: $(SRC)/arquivoBin.c
	$(CC) $(CFLAGS) -o $(BIN)/arquivoBin.o -c $(SRC)/arquivoBin.c

$(BIN)/arquivoCSV.o: $(SRC)/arquivoCSV.c
	$(CC) $(CFLAGS) -o $(BIN)/arquivoCSV.o -c $(SRC)/arquivoCSV.c

$(BIN)/arvoreB.o: $(SRC)/arvoreB.c
	$(CC) $(CFLAGS) -o $(BIN)/arvoreB.o -c $(SRC)/arvoreB.c

$(BIN)/cabecalhoArvB.o: $(SRC)/cabecalhoArvB.c
	$(CC) $(CFLAGS) -o $(BIN)/cabecalhoArvB.o -c $(SRC)/cabecalhoArvB.c

$(BIN)/funcionalidades.o: $(SRC)/funcionalidades.cpp
	$(CC) $(CFLAGS) -o $(BIN)/funcionalidades.o -c $(SRC)/funcionalidades.cpp

$(BIN)/funcoesFornecidas.o: $(SRC)/funcoesFornecidas.c
	$(CC) $(CFLAGS) -o $(BIN)/funcoesFornecidas.o -c $(SRC)/funcoesFornecidas.c	

$(BIN)/grafo.o: $(SRC)/grafo.cpp
	$(CC) $(CFLAGS) -o $(BIN)/grafo.o -c $(SRC)/grafo.cpp

$(BIN)/mensagens.o: $(SRC)/mensagens.c
	$(CC) $(CFLAGS) -o $(BIN)/mensagens.o -c $(SRC)/mensagens.c

$(BIN)/noArvB.o: $(SRC)/noArvB.c
	$(CC) $(CFLAGS) -o $(BIN)/noArvB.o -c $(SRC)/noArvB.c

$(BIN)/registroCabecalho.o: $(SRC)/registroCabecalho.c
	$(CC) $(CFLAGS) -o $(BIN)/registroCabecalho.o -c $(SRC)/registroCabecalho.c

$(BIN)/registroDados.o: $(SRC)/registroDados.c
	$(CC) $(CFLAGS) -o $(BIN)/registroDados.o -c $(SRC)/registroDados.c

$(BIN)/vertice.o: $(SRC)/vertice.cpp
	$(CC) $(CFLAGS) -o $(BIN)/vertice.o -c $(SRC)/vertice.cpp

##--------------------