# Make file program for Project 2 CSC716
# Author: Yu Tian

# the compiler
CC=g++
CC2 = gcc

# compiler flags
CFLAGS=-std=c++14 -pthread
CFLAGS2=-pthread

all: sem monitor testset ex1 ex2 ex3

sem: sem.c
	$(CC2) $(CFLAGS2) -o sem.o sem.c

monitor: monitor.cpp
	$(CC) $(CFLAGS) -o monitor.o monitor.cpp

testset: testset.cpp
	$(CC) $(CFLAGS) -o testset.o testset.cpp

ex1: ex1.c
	$(CC2) $(CFLAGS2) -o ex1.o ex1.c

ex2: ex2.cpp
	$(CC) $(CFLAGS) -o ex2.o ex2.cpp

ex3: ex3.cpp
	$(CC) $(CFLAGS) -o ex3.o ex3.cpp






