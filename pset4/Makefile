# This makefile was adapted from Prof. Aspnes notes

# We STRONGLY recommend putting "-Wall -pedantic -g3" in your CFLAGS.
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g3

all: PlistUnit ClosestPair

PlistUnit: plist_unit.o plist.o point.o
	$(CC) $(CFLAGS) -o $@ $^

ClosestPair: closest_pair.o plist.o point.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) closest_pair plist_unit point plist *.o