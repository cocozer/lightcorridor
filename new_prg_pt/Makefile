# $(BIN) est le nom du binaire généré
BIN = OUICAMARCHYOUPI
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I/
# INCLUDES
LIBS = 
# INCLUDES
LIBDIR = -L/System/Library/Frameworks -lglfw -framework Cocoa -framework OpenGL -framework IOKit
# Compilateur
GCC = g++
# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS = gldrawing.o visu.o create_obj_pt.o

default: $(BIN)

all: $(OBJECT)

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS) 

visu.o: visu.c visu.h
	@echo "**** td1_maze.c ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

gldrawing.o: gldrawing.c gldrawing.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

create_obj_pt.o: create_obj_pt.c create_obj_pt.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
	find . -name "*~" -exec rm {} \;


