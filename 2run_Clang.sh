#!/bin/bash
clang -fpic -c mull.c mull.h
clang -shared -o libmull.so mull.o
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
clang -g -L. -I. -o myapp myapp2.c -lmull
