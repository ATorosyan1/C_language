#include <stdio.h>
#include <math.h>
void app53(int k,int temp)
{
	double p;
	if(temp>k)
            p=(double)(temp/(temp/100+(temp/10)%10+temp%10));
        else
	    p= (double) (temp%10)/temp;       	
	printf("%f\n",p);	
}
void main()
{
	int k,temp;
	printf("k:");
	scanf("%d",&k);
	printf("\n");	
	
	printf("temp:");
	scanf("%d",&temp);
	printf("\n");
	
	app53(k,temp);
}
