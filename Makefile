INC = include
LIB = lib
OBJ = obj
SRC = src
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g -I$(INC) -c
LDFLAGS =  -lGLU -lGL -lglut -L/lib64 -lpthread

all: $(BIN)/main

$(OBJ)/3DObject.o: $(SRC)/3DObject.cc $(INC)/3DObject.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/3DObject.o -g -I$(INC) $(SRC)/3DObject.cc

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cc $(INC)/file_ply_stl.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/file_ply_stl.o -g -I$(INC) $(SRC)/file_ply_stl.cc

$(OBJ)/manageView.o: $(SRC)/manageView.cc $(INC)/manageView.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/manageView.o -g -I$(INC) $(SRC)/manageView.cc

$(OBJ)/models.o: $(SRC)/models.cc $(INC)/models.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/models.o -g -I$(INC) $(SRC)/models.cc

$(OBJ)/objects.o: $(SRC)/objects.cc $(INC)/objects.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/objects.o -g -I$(INC) $(SRC)/objects.cc

$(OBJ)/wattRegulator.o: $(SRC)/wattRegulator.cc $(INC)/wattRegulator.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/wattRegulator.o -g -I$(INC) $(SRC)/wattRegulator.cc

$(OBJ)/button.o: $(SRC)/button.cc $(INC)/button.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/button.o -g -I$(INC) $(SRC)/button.cc

$(OBJ)/fps.o: $(SRC)/fps.cc $(INC)/fps.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/fps.o -g -I$(INC) $(SRC)/fps.cc

$(OBJ)/light.o: $(SRC)/light.cc $(INC)/light.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/light.o -g -I$(INC) -lX11 $(SRC)/light.cc

$(OBJ)/material.o: $(SRC)/material.cc $(INC)/material.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/material.o -g -I$(INC) -lX11 $(SRC)/material.cc

$(OBJ)/texture.o: $(SRC)/texture.cc $(INC)/texture.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/texture.o -g -I$(INC) -lX11 $(SRC)/texture.cc

$(OBJ)/plank.o: $(SRC)/plank.cc $(INC)/plank.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/plank.o -g -I$(INC) $(SRC)/plank.cc

$(OBJ)/camera.o: $(SRC)/camera.cc $(INC)/camera.h
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/camera.o -g -I$(INC) $(SRC)/camera.cc

$(LIB)/libformas.a: $(OBJ)/3DObject.o $(OBJ)/file_ply_stl.o $(OBJ)/manageView.o $(OBJ)/models.o $(OBJ)/wattRegulator.o $(OBJ)/objects.o $(OBJ)/button.o $(OBJ)/fps.o $(OBJ)/light.o $(OBJ)/material.o $(OBJ)/texture.o $(OBJ)/plank.o $(OBJ)/camera.o
	ar rsv $(LIB)/libformas.a $(OBJ)/3DObject.o $(OBJ)/file_ply_stl.o $(OBJ)/manageView.o $(OBJ)/models.o $(OBJ)/wattRegulator.o $(OBJ)/objects.o $(OBJ)/button.o $(OBJ)/fps.o $(OBJ)/light.o $(OBJ)/material.o $(OBJ)/texture.o $(OBJ)/plank.o $(OBJ)/camera.o

$(OBJ)/main.o: $(SRC)/scene.cc
	$(CXX) -c -std=c++17 -O2 -o $(OBJ)/main.o -g -I$(INC) $(SRC)/scene.cc

$(BIN)/main: $(OBJ)/main.o $(LIB)/libformas.a
	$(CXX) -L$(LIB)/ -o $(BIN)/main $(OBJ)/main.o -lformas -lX11 $(LDFLAGS)

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
