#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void app115()
{ 
	double S=0,x=2,ptr;
        for(int i=0;i<=10;i++)
        {
            ptr=i/(pow(4,i)+pow(abs(i),i+2));
            printf("ptr=%f\n",ptr);
            S+=ptr;
        }
        printf("S=%f\n",S);
}
	
void main()
{		
	app115();
}
