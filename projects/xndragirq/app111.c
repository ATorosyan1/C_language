#include <stdio.h>
#include <math.h>
void app111()
{
	double S=0,x=1;
        for(int i=0;i<=10;i++)
        {
            printf("S%f\n",S);
            x=pow(x,4*i+1)/(4*i+1);
            S+=x;
        }
        printf("S=%f\n",S);
	
}
void main()
{		
	app111();
}
