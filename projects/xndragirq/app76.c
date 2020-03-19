#include <stdio.h>
#include <math.h>
void app76()
{
	double y;
        for (double x = -5; x < 5; x += 2) {
           if(x<=0)
               y=0;
           else
               y=x*x+4*pow(x,8);
           printf("x=%f\ty=%f\n",x,y);	
	}
}
void main()
{		
	app76();
}
