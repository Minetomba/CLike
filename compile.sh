#!/bin/bash
tcc main.c -o main
./main "$(cat test.c)"
rm main