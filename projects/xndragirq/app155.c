#include <stdio.h>
#include <math.h>
void app155()
{ 
	int S=0;
        for(int i=10;i<=99;i++)
            if(i%3==0)
                S+=i;
        printf("S=%d\n",S);
}
	
void main()
{		
	app155();
}
