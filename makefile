preprocessor: preprocessor.o stages.o
	gcc -g -ansi -Wall -pedantic preprocessor.o stages.o -o preprocessor 
preprocessor.o: preprocessor.c stages.h
	gcc -c -ansi -Wall -pedantic preprocessor.c -o preprocessor.o 
stages.o : stages.c 
	gcc -c -ansi -Wall -pedantic stages.c -o stages.o
