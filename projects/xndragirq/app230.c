#include <stdio.h>
#include <math.h>
void app230(int * arr,int length)
{ 
        int  S = 0,count=0,k=8;
        for(int i=0;i<length;i++)
            if(arr[i]%k==0)
            {
                count++;
                S+=arr[i]*arr[i];
            }
        printf("%f\n",((double) S/count));
}
	
void main()
{	
	int arr[] ={23, 4, 5, 8, 7, -4, -55, -66, 2, -33, -5};	
	app230(arr,11);
}
