# Makefile created by Shih-Hsiang Cheng B04902023
CPP = g++
INC = -I.
STD = -std=c++98
OPT = -O3
OTHERFLAG = -Wall
CFLAGS = $(INC) $(STD) $(OPT) $(OTHERFLAG)
# object that contain int main() is specified in $MAINOBJ.
MAINOBJ = b04902023_HW3.o
OBJ = b04902023_HW3.o b04902023_HW3_NonogramImage.o b04902023_HW3_NonogramPuzzle.o b04902023_HW3_NonogramSolveAndCreatePuzzle.o
EXE = $(MAINOBJ:.o=)
RM = rm -rf

%.o: %.cpp
	$(CPP) -c -o $@ $< $(CFLAGS)
all: clean $(OBJ)
	$(CPP) -o $(EXE) $(OBJ) $(CFLAGS)
.PHONY: clean run
run:
	./$(EXE)
clean:
	$(RM) $(OBJ) $(EXE)

