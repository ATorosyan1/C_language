#include <stdio.h>
#include <math.h>
void app172(int N)
{ 
	int S=1,ptr;
        ptr=N%2==0?2:1;
        while (N>=ptr) {
            S *= N;
            N-=2;
        }
        printf("S=%d\n",S);
}
	
void main()
{		
	app172(8);
}
