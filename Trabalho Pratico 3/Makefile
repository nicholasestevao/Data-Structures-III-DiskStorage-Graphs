CC := g++
ERROR_WARNINGS := -Werror
DEBUGFLAGS := -g3 -Wall $(ERROR_WARNINGS)
CFLAGS := -std=c++11 -o3 -march=native $(DEBUGFLAGS)

all: trab 

trab:
	$(CC) $(CFLAGS) ./src/*.c ./src/*.cpp -o programaTrab
	
run:
	./programaTrab