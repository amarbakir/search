#/*
# *****************************
# *  214 Systems Programming  *
# *  Fall 2014                *
# *  Author: Amar Bakir       *
# *****************************
# */

CCFLAGS = -Wall -g -o

alldir: lib exec rundir

allfile: lib exec runfile

allsameio: lib exec runsameio

alllong: lib exec runlong

lib: sorted-list.c sorted-listmain.c tokenizer.c
	gcc -c sorted-list.c
	gcc -c sorted-listmain.c
	gcc -c tokenizer.c
	ar rv libi.a sorted-list.o sorted-listmain.o tokenizer.o

exec:
	gcc $(CCFLAGS) indexer indexer.c ./libi.a

rundir: 
	./indexer output.txt testdir

runfile: 
	./indexer output.txt test.txt

runsameio: 
	./indexer sameio.txt sameio.txt

runlong: 
	./indexer output.txt long.txt

clean:
	rm -rf *.o
	rm -rf *.a

