CC = gcc
C_FLAGS = -Wall

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
EXE_DIR = executable
SCRIPT_DIR = scripts

_OBJ = IPC.o signalFunctions.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

_EXE = process1 process2 process3
EXE = $(patsubst %,$(EXE_DIR)/%,$(_EXE))

.PHONY: all clean initialWork

all: initialWork ipcPresenter $(EXE)

initialWork:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)
	cp $(SCRIPT_DIR)/processLaunchScript.sh $(EXE_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	$(CC) $< $(C_FLAGS) -c -o $@

ipcPresenter: src/main.c $(OBJ)
	$(CC) $^ $(C_FLAGS) -o $@

$(EXE_DIR)/process1: src/process1.c $(OBJ)
	$(CC) $^ $(C_FLAGS) -o $@

$(EXE_DIR)/process2: src/process2.c $(OBJ)
	$(CC) $^ $(C_FLAGS) -o $@

$(EXE_DIR)/process3: src/process3.c $(OBJ)
	$(CC) $^ $(C_FLAGS) -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(EXE_DIR)
	rm -f main