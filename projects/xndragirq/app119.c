#include <stdio.h>
#include <math.h>
void app119()
{ 
	double S=0,x=2,ptr;
        for(int i=0;i<=10;i++)
        {
            ptr=sin(3*x+2*i+2)/pow(3,2*i+2);
            printf("ptr=%f\n",ptr);
            S+=ptr;
        }
        printf("S=%f\n",S);
}
	
void main()
{		
	app119();
}
