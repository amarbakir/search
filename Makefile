#/*
# *****************************
# *  214 Systems Programming  *
# *  Fall 2014                *
# *  Author: Amar Bakir       *
# *****************************
# */

CCFLAGS = -Wall -g -o

all: indexer lib exec lib exec run

indexer: libi execi runi

libi: 
	gcc -c -o ./indexer/sorted-list.o ./indexer/sorted-list.c
	gcc -c -o ./indexer/sorted-listmain.o ./indexer/sorted-listmain.c
	gcc -c -o ./indexer/tokenizer.o ./indexer/tokenizer.c
	ar rv ./indexer/libi.a ./indexer/sorted-list.o ./indexer/sorted-listmain.o ./indexer/tokenizer.o

execi:
	gcc $(CCFLAGS) ./indexer/indexer ./indexer/indexer.c ./indexer/./libi.a

runi: 
	./indexer/indexer indexer.txt ./indexer/testdir

lib: sorted-list.c sorted-arraymain.c searchresult.c
	gcc -c  sorted-list.c
	gcc -c sorted-arraymain.c
	gcc -c searchresult.c
	ar rv libs.a sorted-list.o sorted-arraymain.o searchresult.o

exec:
	gcc $(CCFLAGS) search search.c ./libs.a

run: 
	./search indexer.txt

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf ./indexer/*.o
	rm -rf ./indexer/*.a

