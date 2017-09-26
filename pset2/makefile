CC = gcc
CFLAGS = -std=c99 -pedantic -Wall

NoAP: NoAP.o header.o
	${CC} ${CFLAGS} -o NoAP NoAP.o header.o


NoAP.o: NoAP.c header.h
	${CC} ${CFLAGS} -c NoAP.c

header.o: header.c header.h
	${CC} ${CFLAGS} -c header.c

clean:
	$(RM) NoAP *.o
