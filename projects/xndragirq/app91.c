#include <stdio.h>
#include <stdlib.h>
void app91()
{
	int S=0,n=10;
        double x=1;
        for(int i=0;i<=n;i++)
        {
            S+=x;
            printf("%f\n",x);
            x=0.5*abs(x-4);

        }
        printf("S=%d\n",S);
	
}
void main()
{		
	app91();
}
