#include <stdio.h>
#include <math.h>
void app213(int *arr,int length)
{ 
        int count = 0, s = 0;
        for (int i=0; i<length;i++)
            if (arr[i] < 0) {
                s += i*i;
                count++;
            }
        printf("%f\n",((double)s / count));
}
	
void main()
{		
	int arr[] = {23, 4, 5, 66, 7, -4, -5, -6, 2, -3, -5};
	app213(arr,11);
}
