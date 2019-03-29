CC        = gcc
CFLAGS    = -Wall -pedantic #-ansi 
LIBS      = -lpthread -lrt 
CXX       = g++
CXXFLAGS  = -Wall -pedantic

TARGETS   = sum_raceconds_pt_01 sum_mutex_pt_01 prodcons_sem_pt_01 \
            sum_raceconds_01    sum_mutex_01    prodcons_sem_01 \
            matrix

all: $(TARGETS)

sum_raceconds_pt_01: sum_raceconds_pt_01.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

sum_mutex_pt_01: sum_mutex_pt_01.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

sum_sem_pt_01: sum_sem_pt_01.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

prodcons_sem_pt_01: prodcons_sem_pt_01.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

prodcons_sem_pt_02: prodcons_sem_pt_02.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

prodcons_sem_pt_03: prodcons_sem_pt_03.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

sum_raceconds_01: sum_raceconds_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

sum_mutex_01: sum_mutex_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

sum_sem_01: sum_sem_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

prodcons_sem_01: prodcons_sem_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

prodcons_sem_02: prodcons_sem_02.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

prodcons_sem_03: prodcons_sem_03.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

matrix: matrix.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	\rm -f $(TARGETS) *~ core

