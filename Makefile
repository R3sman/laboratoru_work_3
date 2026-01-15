CC = gcc

.PHONY: all clean run install uninstall

all: a.exe

clean:
	rm -rf lab3 *.o
main.o: main.c
	gcc -c -o main.o main.c
stack.o: stack.c
	gcc -c -o stack.o stack.c
sort.o: sort.c
	gcc -c -o sort.o sort.c
operations.o: operations.c
	gcc -c -o operations.o operations.c
lab3: main.o stack.o sort.o operations.o
	gcc -o lab3 main.o stack.o sort.o operations.o

run:
	./a.exe

install:
	install ./lab3 /usr/local/bin
uninstall:
	rm -rf /usr/local/bin/lab3
