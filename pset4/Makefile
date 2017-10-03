CC = gcc
CFLAGS = -std=c99 -pedantic -Wall

unitTest: plist_unit.o point.o point.h plist.o plist.h
	${CC} ${CFLAGS} -o $@ $^

