CC=gcc


default: runtree

mull.o:mull.c mull.h
	$(CC) -c -fpic $^ 

libmull.so:mull.o
	$(CC) -shared $^ -o $@ 


runtree: export LD_LIBRARY_PATH = $(shell pwd)
runtree:libmull.so
	$(CC) -g -L. -I. -o myapp_tree bench_tree.c -lmull
	./myapp_tree


runlist: export LD_LIBRARY_PATH = $(shell pwd)
runlist:libmull.so
	$(CC) -g -L. -I. -o myapp_list bench_list.c -lmull
	./myapp_list

.PHONY: default clean

clean:
	rm -f *.o
