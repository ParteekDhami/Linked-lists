# Define the compiler and flags
CC = gcc -Wall -std=c99 -pedantic
RM = rm -f

default: all

all: q1 q2

q1: q1.c q1_functions.c q1.h
	$(CC) -o q1 q1.c q1_functions.c

q2: q2.c q2_functions.c q2.h
	$(CC) -o q2 q2.c q2_functions.c

clean:
	$(RM) q1 q2
