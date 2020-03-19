#include <stdio.h>
#include <math.h>
void app104()
{
	double S=0,x=-7,y=8;
        for(int i=0;i<10;i++)
        {
            S+=(x*x-2*y);
            printf("x=%f\ty=%f\n",x,y);
            x=sin(x)*sin(x);
            y=y+2;
        }
	
}
void main()
{		
	app104();
}
