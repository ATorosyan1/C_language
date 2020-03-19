#include <stdio.h>
#include <math.h>
void app222(int *arr,int length)
{ 
        int  S = 1,c=3,d=30;
        for(int i=0;i<length;i++)
            if(arr[i]>=c && arr[i]<=d)
                S*=arr[i];
        printf("S=%d\n",S);
}
	
void main()
{	
	int arr[] ={23, 4, 5, 66, 7, -4, -55, -66, 2, -33, -5};	
	app222(arr,11);
}
