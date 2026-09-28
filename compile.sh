#!/bin/bash
tcc parser.c -o parser
tcc lexer.c -o lexer
./lexer "$(cat test.c)" > test.tokens
./parser "$(cat test.tokens)"
rm test.tokens
rm parser
rm lexer