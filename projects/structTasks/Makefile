main:libcollection.a
	gcc main.c -lcollection -L. -o main.out
	./main.out
libcollection.a:stack.o LinkedList.o
	ar -r libcollection.a stack.o LinkedList.o
LinkedList.o:LinkedList.c
	gcc -c LinkedList.c
stack.o:stack.c
	gcc -c stack.c
