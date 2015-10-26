project: libmanagement.o uselibmanagement.o
	cc libmanagement.o uselibmanagement.o -o project

libmanagement.o : libmanagement.c libmanagement.h
		cc -c libmanagement.c

uselibmanagement.o : uselibmanagement.c
		cc -c uselibmanagement.c
