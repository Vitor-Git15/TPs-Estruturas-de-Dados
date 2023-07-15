CC = g++
CXXFLAGS = -std=c++11 -g -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
ANALISAMEM = ../analisamem/bin/analisamem

# all sources, objs, and header files
TARGET = main
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))
EXE = $(BIN_FOLDER)main
# arquivo de entrada
TEST = /tmp/input/test1.txt
all:  mem perf gprof

mem: $(EXE)
	rm -rf /tmp/mem
	mkdir /tmp/mem
	$(EXE) -I $(TEST) -O /tmp/mem/out1.out -P /tmp/mem/out1log.out -L
	rm -rf /tmp/resultmem
	mkdir /tmp/resultmem
	$(ANALISAMEM) -i /tmp/mem/out1log.out -p /tmp/resultmem/result1

perf: $(EXE)
	rm -rf /tmp/perf
	mkdir /tmp/perf
	$(EXE) -I $(TEST) -o /tmp/perf/out1.txt -p /tmp/perf/out1.out

gprof: $(EXE)
	rm -rf /tmp/gprof
	mkdir /tmp/gprof
	$(EXE) -I $(TEST) -o /tmp/gprof/out1.txt7 -p /tmp/gprof/out1.out
	gprof $(EXE) gmon.out > /tmp/gprof/out1gprof.txt

$(BIN_FOLDER)$(TARGET): $(OBJ)
	$(CC) -pg $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)* gmon.out