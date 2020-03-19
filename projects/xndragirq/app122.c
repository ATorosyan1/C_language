#include <stdio.h>
#include <math.h>
void app122()
{ 
	double S=0,x=2,y;
        for(int i=0;i<=10;i++)
        {
            if(i%2!=0)
                x=pow(2.71,i-4);
            else
                x=i*i-i;
             printf("x=%f\n",x);
            if((i*i)%2!=0)
                y=tan(i)*tan(i);
            else
                y=0;
             printf("y=%f\n",y);
           S+=(x*x-y*y);
        }
        printf("S=%f\n",S);
}
	
void main()
{		
	app122();
}
