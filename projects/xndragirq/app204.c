#include <stdio.h>
#include <math.h>
void app204(int n)
{ 
        while(n!=0)
        {
           printf("n=%d\n",n%10);
            n=n/10;
        }
}
	
void main()
{		
	int n=23435435;
	app204(n);
}
