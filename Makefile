INC = include
LIB = lib
OBJ = obj
SRC = src
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g -I$(INC) -c
LDFLAGS =  -lGLU -lGL -lglut

all: $(BIN)/main

$(OBJ)/3DObject.o: $(SRC)/3DObject.cc $(INC)/3DObject.h
	$(CXX) -c -std=c++14 -o $(OBJ)/3DObject.o -g -I$(INC) $(SRC)/3DObject.cc

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cc $(INC)/file_ply_stl.h
	$(CXX) -c -std=c++14 -o $(OBJ)/file_ply_stl.o -g -I$(INC) $(SRC)/file_ply_stl.cc

$(OBJ)/manageView.o: $(SRC)/manageView.cc $(INC)/manageView.h
	$(CXX) -c -std=c++14 -o $(OBJ)/manageView.o -g -I$(INC) $(SRC)/manageView.cc

$(OBJ)/models.o: $(SRC)/models.cc $(INC)/models.h
	$(CXX) -c -std=c++14 -o $(OBJ)/models.o -g -I$(INC) $(SRC)/models.cc

$(OBJ)/objects.o: $(SRC)/objects.cc $(INC)/objects.h
	$(CXX) -c -std=c++14 -o $(OBJ)/objects.o -g -I$(INC) $(SRC)/objects.cc

$(OBJ)/wattRegulator.o: $(SRC)/wattRegulator.cc $(INC)/wattRegulator.h
	$(CXX) -c -std=c++14 -o $(OBJ)/wattRegulator.o -g -I$(INC) $(SRC)/wattRegulator.cc

$(OBJ)/button.o: $(SRC)/button.cc $(INC)/button.h
	$(CXX) -c -std=c++14 -o $(OBJ)/button.o -g -I$(INC) $(SRC)/button.cc

$(LIB)/libformas.a: $(OBJ)/3DObject.o $(OBJ)/file_ply_stl.o $(OBJ)/manageView.o $(OBJ)/models.o $(OBJ)/wattRegulator.o $(OBJ)/objects.o $(OBJ)/button.o
	ar rsv $(LIB)/libformas.a $(OBJ)/3DObject.o $(OBJ)/file_ply_stl.o $(OBJ)/manageView.o $(OBJ)/models.o $(OBJ)/wattRegulator.o $(OBJ)/objects.o $(OBJ)/button.o

$(OBJ)/main.o: $(SRC)/scene.cc
	$(CXX) -c -std=c++14 -o $(OBJ)/main.o -g -I$(INC) $(SRC)/scene.cc

$(BIN)/main: $(OBJ)/main.o $(LIB)/libformas.a
	$(CXX) -L$(LIB)/ -o $(BIN)/main $(OBJ)/main.o -lformas $(LDFLAGS)

#############

clean:
	rm -f ./$(OBJ)/*.o
	rm -f ./$(LIB)/*.a
	rm -f $(BIN)/main

superclean:
	rm -f *.o
	rm *~
	rm -f $(BIN)/main

tgz:
	rm -f *.o
	rm *~
	rm -f $(BIN)/main
	tar -zcvf main.tgz *
