#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void app95()
{
	 double S=0,x=1;
        for(int i=0;i<10;i++) {
            S+=x*x-x;
            printf("%f\n",x);

                x =sin(x)*sin(x);


        }
        printf("S=%f\n",S);
	
}
void main()
{		
	app95();
}
