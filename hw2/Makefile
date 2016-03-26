CPP = g++
INC = -I.
STD = -std=c++98
OPT = -O3
OTHERFLAGS = 
CFLAGS = $(INC) $(STD) $(OPT) $(OTHERFLAGS)
MAINOBJ = b04902023_HW2.o
OBJ = b04902023_HW2.o b04902023_HW2_BigMatrix.o b04902023_HW2_QueryProcess.o b04902023_HW2_BigMatrixHelpInput.o
EXE = $(MAINOBJ:.o=)
RM = rm -rf

%.o: %.cpp
	$(CPP) -c -o $@ $< $(CFLAGS)
all: clean $(OBJ)
	$(CPP) -o $(EXE) $(OBJ) $(CFLAGS)
.PHONY: clean run all
run:
	./$(EXE)
clean:
	$(RM) $(OBJ) $(EXE)
