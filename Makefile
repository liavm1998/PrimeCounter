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
EXECUTABLES = randomGenerator myPrimeCounter myPrimeCounter_only_threads primeCounter

# Default target
all: $(EXECUTABLES)

# Rule to build each executable
randomGenerator: $(OBJ_DIR)/generator.o 
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

