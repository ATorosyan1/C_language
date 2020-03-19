#include <stdio.h>
#include <math.h>
void app57(int a)
{
	double b;
       if(a>300)
                b=(double)((a/10)%10)/(a%10);
       else
       		b=(double)(a/100)/(a%10);
          printf("%f\n",b);	
}
void main()
{
	int a;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	app57(a);
}
