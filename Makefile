all: tm

tm: main.c vm.o parser.o
	gcc -Wall main.c vm.o parser.o -o tm

vm.o: vm.c vm.h
	gcc -Wall -c -g -DDEBUG vm.c

parser.o: parser.c parser.h
	gcc -Wall -c -g -DDEBUG parser.c

