#!/bin/bash
#rm --force *~
#cd bin
#rm --force *
#cd ..
cd lib
rm --force *
#rm --force *.o
cd ..
gcc -Wall -ansi -pedantic -Iinclude -c src/aes_aux_functions.c -o lib/aes_aux_functions.o
gcc -Wall -ansi -pedantic -Iinclude lib/aes_aux_functions.o test/test.c -o test/test_aes.run