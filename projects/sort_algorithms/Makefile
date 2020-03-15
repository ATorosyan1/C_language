main:libsort.a
	gcc  main.c -lsort -L. -g -o  main.out
	./main.out
libsort.a:bublesort.o mergesort.o selectionsort.o insertionsort.o quicksort.o sortarray.o
	ar -r libsort.a bublesort.o mergesort.o sortarray.o insertionsort.o quicksort.o selectionsort.o
bublesort.o:bublesort.c
	gcc -c bublesort.c
mergesort.o:mergesort.c
	gcc -c mergesort.c
selectionsort.o:selectionsort.c
	gcc -c selectionsort.c
insertionsort.o:insertionsort.c
	gcc -c insertionsort.c
quicksort.o:quicksort.c
	gcc -c quicksort.c
sortarray.o:sortarray.c 
	gcc -c sortarray.c
