#include <stdio.h>
#include <math.h>
void app153(int n)
{ 
	 int S=0;
        for(int i=1;i<=n;i++)
            if(n%i==2)
                S+=i;
        printf("S=%d\n",S);
}
	
void main()
{		
	app153(128);
}
