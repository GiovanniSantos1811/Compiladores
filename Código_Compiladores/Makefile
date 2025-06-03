APPS = ./apps
BIN = ./bin
INCLUDES = ./includes
OBJ = ./obj
SRC = ./src


all: 
	gcc -o3 -c $(SRC)/hash.c -I $(INCLUDES) -o $(OBJ)/hash.o
	gcc -o3 -c $(SRC)/arquivo.c -I $(INCLUDES) -o $(OBJ)/arquivo.o
	gcc -o3 -c $(SRC)/lexico.c -I $(INCLUDES) -o $(OBJ)/lexico.o
	gcc -o3 -c $(SRC)/sintatico.c -I $(INCLUDES) -o $(OBJ)/sintatico.o
	gcc -o3 $(APPS)/app.c $(OBJ)/*.o -I $(INCLUDES) -o $(BIN)/app


run:
	./$(BIN)/app

clean: 
	rm $(BIN)/* $(OBJ)/* 

w:
	cls
	make all
	make run