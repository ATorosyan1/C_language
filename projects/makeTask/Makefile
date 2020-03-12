main:libarm.a
	gcc Main.c -larm  -L. -g -o Main.out
	./Main.out
Fibonachi.o:Fibonachi.c
	gcc -c Fibonachi.c
Factorial.o:Factorial.c
	gcc -c Factorial.c
libarm.a:Fibonachi.o Factorial.o
	ar -r  libarm.a Fibonachi.o Factorial.o
