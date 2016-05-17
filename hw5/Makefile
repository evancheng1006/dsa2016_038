# Makefile created by Shih-Hsiang Cheng B04902023
CPP = g++
INC = -I.
STD = -std=c++98
OPT = -O3
DEBUGLEVEL = -DDEBUG=0
OTHERFLAG = -Wall -Werror
CFLAGS = $(INC) $(STD) $(DEBUGLEVEL) $(OPT) $(OTHERFLAG)
# object that contain int main() is specified in $MAINOBJ.
MAINOBJ = main.o
OBJ = main.o queryProcess.o
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

