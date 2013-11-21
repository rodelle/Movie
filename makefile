CC=g++
CFLAGS=-Wall -pedantic -g -c
OBJ=obj

TESTDIR=tests
TESTLIB=tests/lib


test: $(OBJ)/movie.o
	$(CC) -Wall -pedantic -g $(TESTDIR)/movie_test.cpp $(OBJ)/movie.o -I$(TESTLIB) -L$(TESTLIB) -lUnitTest++ -o RunAllTests 
	./RunAllTests

$(OBJ)/test_movie.o: $(TESTDIR)/movie_test.cpp
	$(CC) $(CFLAGS) $(TESTDIR)/movie_test.cpp -o $(OBJ)/test_movie.o

$(OBJ)/movie.o: movie.h movie.cpp 
	$(CC) $(CFLAGS) movie.cpp -o $(OBJ)/movie.o
