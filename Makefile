CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
BOOST_LIB = -lboost_unit_test_framework

PROGRAM = TextWriter
LIBRARY = TextWriter.a
OBJECTS = RandWriter.o
TEST_OBJECTS = test.o RandWriter.o

all: $(PROGRAM) $(LIBRARY) test

$(PROGRAM): TextWriter.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) TextWriter.o RandWriter.o

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

TextWriter.o: TextWriter.cpp RandWriter.hpp
	$(CXX) $(CXXFLAGS) -c TextWriter.cpp

RandWriter.o: RandWriter.cpp RandWriter.hpp
	$(CXX) $(CXXFLAGS) -c RandWriter.cpp

test: $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJECTS) $(BOOST_LIB)

test.o: test.cpp RandWriter.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

lint:
	cpplint *.cpp *.hpp

clean:
	rm -f *.o $(PROGRAM) $(LIBRARY) test