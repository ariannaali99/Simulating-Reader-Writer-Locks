#Readers-Writers Makefile by Arianna Ali

#C Compiler
CC = gcc

#Compiler Flags
CFLAGS = -l pthread

#Target Executable
run: rwmain
	./rwmain 

rwmain: main.o 
	$(CC) $(CFLAGS) -o rwmain main.o readerwriter.o

main.o: main.c readerwriter.c 
	$(CC) $(CFLAGS) -c main.c

readerwriter.o: readerwriter.c readerwriter.h
	$(CC) $(CFLAGS) -c readerwriter.c
