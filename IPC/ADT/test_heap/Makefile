help:
	@echo "make help"
	@echo "make all"


ADT_heap.o: ADT_heap.c
	g++ -c ADT_heap.c

main.o: main.c
	g++ -c main.c

all: ADT_heap.o main.o
	g++ -g -o heap main.o ADT_heap.o

run: all
	heap

clean:
	del *.o

cleanup: clean
	del *.exe
