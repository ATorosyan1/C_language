#include <stdio.h>
#include <math.h>
void app126()
{ 
	double S=0,x,y,k;
        for(int i=0;i<=10;i++)
        {
            k=(double)i;
            if((k/5)==(int)(k/5)){
                x=i;}
            else
                x=0;
             printf("x=%f\n",x);
            if((k/7)==(int)(k/7))
                y=i*i;
            else
                y=i;
             printf("y=%f\n",y);
            S+=(x-y);
        }
        printf("S=%f\n",S);
}
	
void main()
{		
	app126();
}
