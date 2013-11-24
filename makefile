CC=g++
CFLAGS=-Wall -pedantic -g -c -w
OBJ=obj

TESTDIR=tests

TESTINCLUDE=-Itests/lib -Ltests/lib -lUnitTest++
BOOSTINCLUDE=-I/usr/include -L/usr/lib

test: $(OBJ)/movie_test.o $(OBJ)/comedy_test.o $(OBJ)/test_helper.o $(OBJ)/movie.o $(OBJ)/comedy.o $(TESTDIR)/main.cpp
	$(CC) -Wall -pedantic -g $(TESTDIR)/main.cpp $(OBJ)/comedy_test.o $(OBJ)/movie_test.o $(OBJ)/movie.o $(OBJ)/comedy.o $(OBJ)/test_helper.o $(TESTINCLUDE) -o RunAllTests 
	./RunAllTests

$(OBJ)/test_helper.o: $(TESTDIR)/test_helper.h $(TESTDIR)/test_helper.cpp
	$(CC) $(CFLAGS) $(TESTDIR)/test_helper.cpp -o $(OBJ)/test_helper.o

$(OBJ)/movie_test.o: $(TESTDIR)/movie_test.cpp $(OBJ)/movie.o $(OBJ)/test_helper.o
	$(CC) $(CFLAGS) $(TESTDIR)/movie_test.cpp $(TESTINCLUDE) -o $(OBJ)/movie_test.o

$(OBJ)/comedy_test.o: $(TESTDIR)/comedy_test.cpp $(OBJ)/comedy.o $(OBJ)/test_helper.o
	$(CC) $(CFLAGS) $(TESTDIR)/comedy_test.cpp $(TESTINCLUDE) -o $(OBJ)/comedy_test.o

$(OBJ)/movie.o: movie.h movie.cpp $(OBJ)/boost.o
	$(CC) $(CFLAGS) movie.cpp -o $(OBJ)/movie.o

$(OBJ)/comedy.o: comedy.h comedy.cpp $(OBJ)/movie.o $(OBJ)/boost.o
	$(CC) $(CFLAGS) comedy.cpp -o $(OBJ)/comedy.o

$(OBJ)/boost.o: boost.cpp
	$(CC) $(CFLAGS) $(BOOSTINCLUDE) boost.cpp -o $(OBJ)/boost.o

clean:
	rm $(OBJ)/*.o
