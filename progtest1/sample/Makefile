CXX=g++
LD=g++
AR=ar
CXXFLAGS=-std=c++14 -Wall -pedantic -O2

all: test

deps:
	g++ -MM *.cpp > Makefile.d

test: solution.o sample_tester.o
	$(LD) $(CXXFLAGS) -o $@ $^ -L. -lprogtest_solver -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lib: progtest_solver.o
	$(AR) cfr libprogtest_solver.a $^

clean:
	rm -f *.o test *~ core sample.tgz
	
clear:
	rm -f *.o test *~ core sample.tgz Makefile.d *.a
	
pack:
	rm -f sample.tgz
	tar zcf sample.tgz *.h *.a Makefile* solution.cpp sample_tester.cpp
	

-include Makefile.d
