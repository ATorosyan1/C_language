#include <stdio.h>
#include <math.h>
void app151(int n)
{ 
	 int S=0;
    	 for(int i=1;i<=n;i++)
         if(n%i==0)
             S+=i;
        printf("S=%d\n",S);
}
	
void main()
{		
	app151(128);
}
