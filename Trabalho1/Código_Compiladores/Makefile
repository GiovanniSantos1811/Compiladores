APPS = ./apps
BIN = ./bin
INCLUDES = ./includes
OBJ = ./obj
SRC = ./src


all: 
	gcc -o3 -c $(SRC)/hash.c -I $(INCLUDES) -o $(OBJ)/hash.o
	gcc -o3 -c $(SRC)/arquivo.c -I $(INCLUDES) -o $(OBJ)/arquivo.o
	gcc -o3 -c $(SRC)/automato.c -I $(INCLUDES) -o $(OBJ)/automato.o
	gcc -o3 $(APPS)/teste.c $(OBJ)/*.o -I $(INCLUDES) -o $(BIN)/teste

run:
	./$(BIN)/teste

clean: 
	rm $(BIN)/* $(OBJ)/* 