help:
	@echo "make help"
	@echo "make all"


all:
	g++ -g -pg -o path main.c ADT_graph.c ADT_llist.c ADT_queue.c ADT_stack.c ADT_heap.c ADT_Dijkstra.c ADT_create_Map.c

run: all
	path

clean:
	del *.o

cleanup: clean
	del *.exe
