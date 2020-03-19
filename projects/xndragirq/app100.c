#include <stdio.h>
#include <math.h>
void app100()
{
	double S=1,x=1;
        for(int i=10;i>=0;i--)
        {
            S*=x;
        printf("x=%f\n",x);
            x=atan(1/(x-1));
        }
        printf("S=%f\n",S);
	
}
void main()
{		
	app100();
}
