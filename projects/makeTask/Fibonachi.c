#include <stdio.h>
int fibonachi(int n)
{
	if(n==2)
	   return 2;
	if(n==1)
	   return 1;
	return fibonachi(n-1)+fibonachi(n-2);
}
