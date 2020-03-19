#include <stdio.h>
#include <math.h>
void app201(int n)
{ 
	int S=0;
        while(n!=0)
        {
            S++;
            n=n/10;
        }
        printf("S=%d\n",S);
}
	
void main()
{	
	int n=23435435;	
	app201(n);
}
