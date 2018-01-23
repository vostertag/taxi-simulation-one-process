CC = gcc

output: main.o readData.o taxis.o
	$(CC) main.o readData.o taxis.o -o output

main.o: main.c
	$(CC) -c main.c

readData.o: readData.c
	$(CC) -c readData.c

taxis.o: taxis.c
	$(CC) -c taxis.c

clean: 
	rm *.o output