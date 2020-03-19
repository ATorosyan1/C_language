#include <stdio.h>
#include <math.h>
void app163()
{ 
	int a;
        double b;
        short t=0;
        for(double i=9999;i>=1000;i--)
        {
            a =(int) sqrt(i * 18);
            b=sqrt(i * 18);
            if((double)a==b) {
                t=1;
                printf("%d\n",(int)i);
                break ;
            }

        }
        if(t==0)
            printf("Invalid number!!!\n");
}
	
void main()
{		
	app163();
}
