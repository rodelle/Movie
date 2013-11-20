movie: movie.o 
	g++ -Wall -g lib/movie.o

test: movie.o
	g++ -o RunAllTests ./tests/movie_test.cpp lib/movie.o -I./tests/lib/ -L./tests/lib/ -lUnitTest++
	./RunAllTests

movie.o: movie.h movie.cpp 
	g++ -Wall -g -c movie.cpp
	mv movie.o lib/
