#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Vitor Emanuel Ferreira Vital (vitorvital@dCXX.ufmg.br)
# Histórico	: 2022-04-29 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CXX = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
TEST = test
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.hpp $(INC)/memlog.hpp $(INC)/msgassert.hpp
CFLAGS = -pg -std=c++11 -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/matop

all:  mem perf gprof

mem: $(EXE)
	rm -rf /tmp/mem
	mkdir /tmp/mem
	$(EXE) -1 $(TEST)/m1.txt -2 $(TEST)/m2.txt -o /tmp/mem/somaresult.out -s -p /tmp/mem/somalog.out -l
	rm -rf /tmp/somadin
	mkdir /tmp/somadin
	$(ANALISAMEM) -i /tmp/mem/somalog.out -p /tmp/somadin/somadin

	$(EXE) -1 $(TEST)/m1.txt -2 $(TEST)/m2.txt -o /tmp/mem/multresult.out -m -p /tmp/mem/multlog.out -l
	rm -rf /tmp/multin
	mkdir /tmp/multin
	$(ANALISAMEM) -i /tmp/mem/multlog.out -p /tmp/multin/multin

	$(EXE) -1 $(TEST)/m1.txt -o /tmp/mem/transpresult.out -t -p /tmp/mem/transplog.out -l
	rm -rf /tmp/transpin
	mkdir /tmp/transpin
	$(ANALISAMEM) -i /tmp/mem/transplog.out -p /tmp/transpin/transpin

perf: $(EXE)
	rm -rf /tmp/perf
	mkdir /tmp/perf
	$(EXE) -1 $(TEST)/m1.txt -2 $(TEST)/m2.txt -o /tmp/perf/somaresult.txt -s -p /tmp/perf/soma10.out
	$(EXE) -1 $(TEST)/m1.txt -2 $(TEST)/m2.txt -o /tmp/perf/multresult.txt -m -p /tmp/perf/mult10.out
	$(EXE) -1 $(TEST)/m1.txt -o /tmp/perf/transpresult.txt -t -p /tmp/perf/transp10.out

gprof: $(BIN)/matop
	rm -rf /tmp/gprof
	mkdir /tmp/gprof
	$(EXE) -1 $(TEST)/m1.txt -2 $(TEST)/m2.txt -o /tmp/gprof/somagprof.txt -s -p /tmp/gprof/soma10.out
	gprof $(EXE) gmon.out > /tmp/gprof/somagprof.txt
	$(EXE) -m -1 $(TEST)/m1.txt -2 $(TEST)/m2.txt -o /tmp/gprof/multgprof.txt -p /tmp/gprof/mult10.out
	gprof $(EXE) gmon.out > /tmp/gprof/multgprof.txt
	$(EXE)  -1 $(TEST)/m1.txt -o /tmp/gprof/transpgprof.txt -t -p /tmp/gprof/transp10.out
	gprof $(EXE) gmon.out > /tmp/gprof/transpgprof.txt
	

$(BIN)/matop: $(OBJS)
	$(CXX) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.cpp
	$(CXX) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.cpp 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.cpp
	$(CXX) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
