LIBS = -lsqlite3 
CXX = g++
CXXFLAGS = -g -march=native -pipe  -pthread

example: example.o  nanosql.o nanosql.hpp
	$(CXX) example.o nanosql.o $(LIBS) $(CXXFLAGS) -o test

clean:
	rm *.o
