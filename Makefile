CC=g++
CA=as
LD=g++
MV=mv
RM=rm
MKDIR=mkdir

CCFLAGS=-g -I include -c -std=c++11 -Werror -Wextra -Wall
LDFLAGS=

SRC_CPP=./src/InstructionList.cpp ./src/InstructionPack.cpp ./src/Lexer.cpp ./src/Loop.cpp ./src/Pack.cpp ./src/ParseError.cpp ./src/Program.cpp ./src/main.cpp

OBJ_CPP=$(patsubst ./src/%.cpp,./obj/%.o,$(SRC_CPP))
OBJ=$(OBJ_CPP)

all: prepare bfc

# CPP -> O
obj/%.o:src/%.cpp
	$(CC) $< $(CCFLAGS) -o $@

bfc: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ) 

prepare:
	$(MKDIR) -p obj

clean::
	$(RM) -rf obj
	$(RM) -f bfc

# EOF
