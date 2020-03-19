#include <stdio.h>
#include <math.h>
void app219(int * arr,int length)
{ 
        int  S = 0,k=3;
        for(int i=0;i<length;i++)
            if(i%k==0)
                S++;
        printf("S=%d\n",S);
}
	
void main()
{	
	int arr[] = {23, 4, 5, 66, 7, -4, -55, -66, 2, -33, -5};	
	app219(arr,11);
}
