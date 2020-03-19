#include <stdio.h>
#include <math.h>
void app80()
{
	double y=0;
        for(double x=-5;x<=5;x+=2) {
            if (x > 5)
                y = pow(2, (5 - x));
            else
                y = 7 - x;
           	printf("x=%f\ty=%f\n",x,y);	
	}
	
}
void main()
{		
	app80();
}
