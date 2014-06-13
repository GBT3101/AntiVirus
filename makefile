
# All Targets
all: runFile


runFile: bin/main.o
	gcc -m32 -g -Wall -o bin/task3 bin/main.o

bin/main.o: main.c
	gcc -m32 -g -c -o bin/main.o main.c


#Clean the build directory
clean:
	rm -f bin/*
