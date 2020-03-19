#include <stdio.h>
#include <math.h>
void app216(int * arr,int length)
{ 
        int  S = 1;
        for(int i=0;i<length;i+=2)
            S*=arr[i];
        printf("S=%d\n",S);
}
	
void main()
{	
	int arr[] = {23, 4, 5, 66, 7, -4, -55, -66, 2, -33, -5};	
	app216(arr,11);
}
