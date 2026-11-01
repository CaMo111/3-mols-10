#!/bin/bash

rm -rf 1
rm -rf 2
rm -rf 3
rm -rf 4
rm -rf 5
gcc -O3 -march=native                              -o 1  net5.c
gcc -O3 -march=native -DTYPE_COMMON                -o 2  net5.c
gcc -O3 -march=native -DCLASS_MOST                 -o 3    net5.c
gcc -O3 -march=native -DCLASS_MOST -DTYPE_COMMON   -o 4    net5.c

