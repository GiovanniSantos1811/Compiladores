APPS = ./apps
BIN = ./bin
INCLUDES = ./includes
OBJ = ./obj
SRC = ./src


all: 
	gcc -o3 -c $(SRC)/hash.c -I $(INCLUDES) -o $(OBJ)/hash.o
	gcc -o3 -c $(SRC)/arquivo.c -I $(INCLUDES) -o $(OBJ)/arquivo.o
	gcc -o3 -c $(SRC)/lexico.c -I $(INCLUDES) -o $(OBJ)/lexico.o
	gcc -o3 $(APPS)/teste.c $(OBJ)/*.o -I $(INCLUDES) -o $(BIN)/teste


run:
	./$(BIN)/teste

clean: 
	rm $(BIN)/* $(OBJ)/* 

w:
	cls
	make all
	make run