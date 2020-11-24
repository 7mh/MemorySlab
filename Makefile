CC=gcc

clean:
	rm -f *.o

all: runtree runlist

mull.o:mull.c mull.h
	$(CC) -c -fpic $^ 

libmull.so:mull.o
	$(CC) -shared $^ -o $@ 


runtree: export LD_LIBRARY_PATH = $(shell pwd)
runtree:libmull.so
	$(CC) -g -L. -I. -o myapp_tree slabbench.c -lmull
	./myapp_tree


runlist: export LD_LIBRARY_PATH = $(shell pwd)
runlist:libmull.so
	$(CC) -g -L. -I. -o myapp_list myapp2.c -lmull
	./myapp_list


