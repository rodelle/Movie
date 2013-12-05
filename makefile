CXX=g++

OBJ_DIR=obj
TEST_DIR=tests

TESTLIB=-Ltests/lib -lUnitTest++
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
			afactory.cpp \
			action.cpp \
			transaction.cpp \
			borrow.cpp \
			return.cpp \
			showmovies.cpp \
			displaycustomerhistory.cpp \
			store.cpp \
			hashtable.cpp \

objects = $(src:%.cpp=%.o)

main: $(objects) main.cpp
	$(CXX) $(objects) main.cpp -o MOVIE
	./MOVIE

$(OBJ_DIR)/%.o: %.cpp 
	$(CXX) $< -o $@

clean:
	rm $(objects)
