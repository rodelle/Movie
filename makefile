CXX=g++
CXXFLAGS=-Wall -pedantic -c

OBJ_DIR=obj
TEST_DIR=tests

TESTINCLUDE=-Itests/lib -Ltests/lib -lUnitTest++
BOOSTINCLUDE=-I/usr/include -L/usr/lib

src = movie.cpp \
			comedy.cpp \
			drama.cpp \

test_src = test_main.cpp \
					 test_helper.cpp \
					 movie_test.cpp \
					 drama_test.cpp \
					 comedy_test.cpp \

objects = $(src:%.cpp=$(OBJ_DIR)/%.o)
test_objects = $(test_src:%.cpp=$(OBJ_DIR)/%.o)

test: $(objects) $(test_objects)
	$(CXX) -Wall -pedantic $(objects) $(test_objects) $(TESTINCLUDE) -o RunAllTests 
	./RunAllTests

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TESTINCLUDE) $< -o $@

$(OBJ_DIR)/%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/boost.o: boost.cpp 
	$(CXX) $(CXXFLAGS) $(BOOSTINCLUDE) $< -o $@

clean:
	rm $(objects) $(test_objects)
