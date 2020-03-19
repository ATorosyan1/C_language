#include <stdio.h>
#include <math.h>
void app207(int n)
{ 
        short t=0;
        while(n!=0)
        {
            if(n%10==2)
                t=1;
            n=n/10;
        }
	if(t==1)
            printf("true\n");
	else
	    printf("false\n");
}
	
void main()
{		
	int n=334235435;
	app207(n);
}
