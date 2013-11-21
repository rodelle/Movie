CC=g++
CFLAGS=-Wall -pedantic -g -c
OBJ=obj

TESTDIR=tests
TESTLIB=tests/lib

BOOSTINCLUDE=-I/usr/include -L/usr/lib

test: $(OBJ)/movie.o
	$(CC) -Wall -pedantic -g $(TESTDIR)/movie_test.cpp $(OBJ)/movie.o -I$(TESTLIB) -L$(TESTLIB) -lUnitTest++ -o RunAllTests 
	./RunAllTests

$(OBJ)/test_movie.o: $(TESTDIR)/movie_test.cpp
	$(CC) $(CFLAGS) $(TESTDIR)/movie_test.cpp -o $(OBJ)/test_movie.o

$(OBJ)/movie.o: movie.h movie.cpp $(OBJ)/boost.o
	$(CC) $(CFLAGS) movie.cpp $(OBJ)/boost.o -o $(OBJ)/movie.o

$(OBJ)/boost.o: boost.cpp
	$(CC) $(CFLAGS) $(BOOSTINCLUDE) -lboost_date_time boost.cpp -o $(OBJ)/boost.o
