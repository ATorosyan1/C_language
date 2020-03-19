#include <stdio.h>
#include <stdlib.h>
void app108()
{
	double S=0,x=1,y=1;
        for(int i=0;i<=10;i++)
        {
            S+=x+y*y;
            printf("x=%f\ty=%f\n",x,y);
            x=5*abs(x+3);
            y=5*y+2;
        }
        printf("S=%f\n",S);
	
}
void main()
{		
	app108();
}
