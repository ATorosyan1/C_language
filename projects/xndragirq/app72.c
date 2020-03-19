#include <stdio.h>
#include <math.h>
void app72()
{
	double y,m;
        for (double x = -5.4; x < 1.2; x += 0.4) {
            y = (1/tan(x*x)*1/tan(x*x));
            printf("x=%f\ty=%f\n",x,y);	
        }
}
void main()
{	
	app72();
}
