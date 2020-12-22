#!/bin/bash
gcc -fpic -c mull.c mull.h
gcc -shared -o libmull.so mull.o
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
gcc -g -L. -I. -o myapp_tree bench_tree.c -lmull
./myapp_tree
