
BUILD_FLAGS = -std=c++11
CC = g++
RM = rm
EXES = *.exe
OBJECTS = *.o
OUTPUT = *.out

all: clean driver.exe

implementation.o: Makefile implementation.cpp
	$(CC) $(BUILD_FLAGS) -c implementation.cpp -o implementation.o

driver.exe: Makefile implementation.o driver.cpp
	$(CC) $(BUILD_FLAGS) implementation.o driver.cpp -o driver.exe

clean:
	$(RM) -f $(EXES) $(OBJECTS) $(OUTPUT)
