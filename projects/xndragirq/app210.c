#include <stdio.h>
#include <math.h>
void app210(int n)
{ 
	int k=0,s=0;
        while(n!=0)
        {
           k+=n%10;
           n=n/10;
           s+=n%10;
           n=n/10;
        }
	if(k==s)
        	printf("true\n");
	else
		printf("false\n");
}
	
void main()
{	
	int n=114224;	
	app210(n);
}
