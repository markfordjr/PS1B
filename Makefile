CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system

DEPS = FibLFSR.hpp PhotoMagic.hpp
OBJECTS = FibLFSR.o PhotoMagic.o
PROGRAM = PhotoMagic

TEST = test

.PHONY: all clean lint PhotoMagic.a

all: $(PROGRAM) $(TEST)

$(PROGRAM): main.o $(OBJECTS) PhotoMagic.a
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o $(OBJECTS) $(LIB)

$(TEST): test.o $(OBJECTS) PhotoMagic.a
	$(CC) $(CFLAGS) -o $(TEST) test.o $(OBJECTS) $(LIB)

main.o: main.cpp $(DEPS)
	$(CC) $(CFLAGS) -o main.o -c main.cpp

test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -o test.o -c test.cpp

FibLFSR.o: FibLFSR.cpp FibLFSR.hpp
	$(CC) $(CFLAGS) -o FibLFSR.o -c FibLFSR.cpp

PhotoMagic.o: PhotoMagic.cpp PhotoMagic.hpp
	$(CC) $(CFLAGS) -o PhotoMagic.o -c PhotoMagic.cpp

PhotoMagic.a: $(OBJECTS)
	ar rcs PhotoMagic.a $(OBJECTS)

clean:
	rm -f *.o $(PROGRAM) $(TEST) PhotoMagic.a

lint:
	cpplint *.cpp *.hpp
