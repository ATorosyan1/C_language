#include <stdio.h>
#include <stdlib.h>
void app98()
{
	double S=0,x=1;
        for(int i=0;i<=10;i++)
        {
            S+=x;
            printf("x:%f\n",x);
           x=3.4*abs(x-7);
        }
        printf("S:%f\n",S);
	
}
void main()
{		
	app98();
}
