# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SOURCES = $(SRC_DIR)/generator.c $(SRC_DIR)/myPrimeCounter.c $(SRC_DIR)/myPrimeCounter_only_threads.c $(SRC_DIR)/primeCounter.c $(SRC_DIR)/queue.c

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Executable names
EXECUTABLES = generator myPrimeCounter myPrimeCounter_only_threads primeCounter

# Default target
all: $(EXECUTABLES)

# Rule to build each executable
generator: $(OBJ_DIR)/generator.o $(OBJ_DIR)/queue.o
	$(CC) $(CFLAGS) -o $@ $^

myPrimeCounter: $(OBJ_DIR)/myPrimeCounter.o $(OBJ_DIR)/queue.o
	$(CC) $(CFLAGS) -o $@ $^

myPrimeCounter_only_threads: $(OBJ_DIR)/myPrimeCounter_only_threads.o $(OBJ_DIR)/queue.o
	$(CC) $(CFLAGS) -o $@ $^

primeCounter: $(OBJ_DIR)/primeCounter.o $(OBJ_DIR)/queue.o
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLES)

# .PHONY: all
# all: generator primeCounter myprimeCounter threadsOnly

# generator:  src/generator.c
# 	gcc -o randomGenerator src/generator.c

# primeCounter:	src/primeCounter.c
# 	gcc -o primeCounter src/primeCounter.c

# myprimeCounter:	src/myprimeCounter.c
# 	gcc -o myprimeCounter src/myprimeCounter.c

# threadsOnly:	src/myprimeCounter_only_threads.c
# 	gcc -o threadsOnly src/myprimeCounter_only_threads.c

# .PHONY: clean
# clean:
# 	-rm -f randomGenerator primeCounter myprimeCounter sharedMem 2>/dev/null
