CC=gcc
CFLAGS=-Wall -pedantic
PRIMELIBS=-lpthread -lm
TRAINLIBS=-lpthread -lrt
MATRIXLIBS=-lpthread
TARGETS=prime1 prime2 prime3 prime4 prime5 prime6 prime7 prime8 prime9 train1 train2 train3 train4 matrix
CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic

all: $(TARGETS)

prime1: prime1.c
	$(CC) $(CFLAGS) -o $@ $< -lm

prime2: prime2.c
	$(CC) $(CFLAGS) -o $@ $< $(PRIMELIBS)

prime3: prime3.c
	$(CC) $(CFLAGS) -o $@ $< $(PRIMELIBS)

prime4: prime4.c
	$(CC) $(CFLAGS) -o $@ $< $(PRIMELIBS)

prime5: prime5.c
	$(CC) $(CFLAGS) -o $@ $< $(PRIMELIBS)

prime6: prime6.c
	$(CC) $(CFLAGS) -o $@ $< $(PRIMELIBS)

prime7: prime7.c
	$(CC) $(CFLAGS) -o $@ $< $(PRIMELIBS)

prime8: prime8.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(PRIMELIBS)

prime9: prime9.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(PRIMELIBS)

train1: train1.c
	$(CC) $(CFLAGS) -o $@ $< $(TRAINLIBS)

train2: train2.c
	$(CC) $(CFLAGS) -o $@ $< $(TRAINLIBS)

train3: train3.c
	$(CC) $(CFLAGS) -o $@ $< $(TRAINLIBS)

train4: train4.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(TRAINLIBS)

matrix: matrix.c
	$(CC) $(CFLAGS) -o $@ $< $(MATRIXLIBS)

clean:
	rm -f $(TARGETS) core *~
