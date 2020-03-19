#include <stdio.h>
#include <math.h>
void app166(int n)
{ 
	int y=0;
        for (int i = 0; i < n / 2; i++)
            if(pow(4,i)==n){
                y=1;
                break;
            }
        printf("y=%d\n",y);
}
	
void main()
{		
	app166(45);
}
