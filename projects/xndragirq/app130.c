#include <stdio.h>
#include <math.h>
void app130()
{ 
	double S=1,x,y,k;
        for(int i=1;i<=10;i++)
        {
            k=(double)i;
            if((k/5)==(int)(k/5))
                x=i;
            else
                x=i*i;
            printf("x=%f\n",x);
            if((k/3)==(int)(k/3))
                y=i*i*i;
            else
                y=6;
            printf("y=%f\n",y);
            S*=(x*y);
        }
        printf("S=%f\n",S);
}
	
void main()
{		
	app130();
}
