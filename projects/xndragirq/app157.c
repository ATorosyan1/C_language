#include <stdio.h>
#include <math.h>
void app157()
{ 
	int S=0;
        for(int i=100;i<=999;i++)
            if(i%5==0)
                S+=i;
        printf("S=%d\n",S);
}
	
void main()
{		
	app157();
}
