CC = gcc
CFLAGS = -std=c99 -pedantic -Wall

NoAP: NoAP.o
	${CC} ${CFLAGS} -o NoAP NoAP.o

NoAP.o: NoAP.c
	${CC} ${CFLAGS} -c NoAP.c

clean:
	$(RM) NoAP *.o
