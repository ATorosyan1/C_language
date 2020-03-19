#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void app225(int * arr,int length)
{ 
        int  S = 1,t=8;
        for(int i=0;i<length;i++)
            if(abs(arr[i])<t)
                S*=arr[i];
        printf("S=%d\n",S);
}
	
void main()
{	
	int arr[] ={23, 4, 5, 66, 7, -4, -55, -66, 2, -33, -5};	
	app225(arr,11);
}
