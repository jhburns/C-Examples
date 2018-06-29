
BUILD_FLAGS = -std=c++11
CC = g++
RM = rm
EXES = *.exe
OBJECTS = *.o
OUTPUT = *.out

all: clean driver.exe

imp.o: Makefile imp.cpp
	$(CC) $(BUILD_FLAGS) -c imp.cpp -o imp.o

driver.exe: Makefile imp.o driver.cpp
	$(CC) $(BUILD_FLAGS) imp.o driver.cpp -o driver.exe

clean:
	$(RM) -f $(EXES) $(OBJECTS) $(OUTPUT)
