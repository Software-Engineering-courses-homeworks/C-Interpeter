CC=gcc

main.o: main.c
	CC -c main.c

clean:
	rm *.o