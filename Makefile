# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude -I/usr/include/CUnit

# Linker flags
LDFLAGS = -lcunit -lm

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SOURCES = $(SRC_DIR)/generator.c $(SRC_DIR)/myPrimeCounter.c $(SRC_DIR)/myPrimeCounter_only_threads.c $(SRC_DIR)/primeCounter.c $(SRC_DIR)/queue.c

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Executable names
EXECUTABLES = randomGenerator myPrimeCounter myPrimeCounter_only_threads primeCounter test_isPrime

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

# Rule to build the test executable
test_isPrime: test_isPrime.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build the test object file
test_isPrime.o: tests/test_isPrime.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_generator: test_generator.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build the test object file
test_generator.o: tests/test_generator.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_isPrime: test_isPrime.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build the test object file
test_isPrime.o: tests/test_isPrime.c
	$(CC) $(CFLAGS) -c -o $@ $<


# Rule to run the test
test: test_generator test_isPrime
	./test_generator
	./test_isPrime

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLES) test_isPrime test_isPrime.o
