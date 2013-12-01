CXX=g++
CXXFLAGS=-Wall -pedantic -c

OBJ_DIR=obj
TEST_DIR=tests

TESTLIB=-Ltests/lib -lUnitTest++
TESTINCLUDE=-Itests/lib
BOOSTINCLUDE=-I/usr/include -L/usr/lib

src = movie.cpp \
			comedy.cpp \
			drama.cpp \
			classic.cpp \
			inventoryitem.cpp \
			mfactory.cpp \
			mcollection.cpp \
			customer.cpp \
			scustomer.cpp \
			ccollection.cpp \
			transaction.cpp \
			rent.cpp \
			return.cpp \

test_src = test_main.cpp \
					 test_helper.cpp \
					 drama_test.cpp \
					 comedy_test.cpp \
					 classic_test.cpp \
					 inventoryitem_test.cpp \
					 mfactory_test.cpp \
					 mcollection_test.cpp \
					 customer_test.cpp \
					 scustomer_test.cpp \
					 ccollection_test.cpp \
					 transaction_test.cpp \

objects = $(src:%.cpp=$(OBJ_DIR)/%.o)
test_objects = $(test_src:%.cpp=$(OBJ_DIR)/%.o)

test: $(objects) $(test_objects)
	$(CXX) -Wall -pedantic $(objects) $(test_objects) $(TESTLIB) -o RunAllTests 
	./RunAllTests

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TESTINCLUDE) $< -o $@

$(OBJ_DIR)/%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/boost.o: boost.cpp 
	$(CXX) $(CXXFLAGS) $(BOOSTINCLUDE) $< -o $@

clean:
	rm $(objects) $(test_objects)
