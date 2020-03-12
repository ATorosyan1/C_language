#include <stdio.h>
#define K 6
int fibonachi(int n);
int factorial(int n);
int main()
{
	printf("Fibonachi(%d)=%d\n", K,fibonachi(K));
	printf("Factorial(%d)=%d\n" ,K,factorial(K));
	return 0;
}
