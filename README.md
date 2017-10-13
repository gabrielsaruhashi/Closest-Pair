## Closest Pair
A C program that implements the O(nlogn)O(nlog⁡n) divide-and-conquer algorithm for CLOSEST-PAIR. Utilizes an opaque array-based ListOfPoints ADT.

Program reads the points from standard input and writes the result to standard output. The first line of input will be an integer giving the number of points; there will be at least two points. The following lines of input will contain the coordinates of the points, with one point per line and with each line containing the x-coordinate of a point followed by the y-coordinate, separated by whitespace (and with possibly leading and trailing whitespace on each line); all the points will be distinct. Each coordinate will be a decimal floating-point value suitable for parsing by atof with no extra characters that would prevent atof from examining the entire input.

#Run
	make
	./ClosestPair < input.txt

