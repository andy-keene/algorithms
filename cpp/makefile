CC = g++
flags = -Wall -g -std=c++11
exe = app

#Do I need to include the .h's for every .o file?

all: app

app: quicksort.o mergesort.o helpers.o main.o
	$(CC) quicksort.o mergesort.o helpers.o main.o -o $(exe)

quicksort.o: quicksort.cpp quicksort.h
	 $(CC) $(flags) -c quicksort.cpp

mergesort.o: mergesort.cpp mergesort.h 
	$(CC) $(flags)  -c mergesort.cpp

helpers.o: helpers.cpp helpers.h
	$(CC) $(flags) -c helpers.cpp

main.o: main.cpp quicksort.h mergesort.h helpers.h
	$(CC) $(flags) -c main.cpp

clean:
	rm *.o $(exe)

