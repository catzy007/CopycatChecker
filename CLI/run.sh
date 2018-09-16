#!/bin/bash
gcc -c main.c
gcc -c checkcopy.c
gcc checkcopy.o main.o -o main
./main
rm main.o
rm checkcopy.o

