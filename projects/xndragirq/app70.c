#include <stdio.h>
#include <math.h>
void app70(int a)
{
	int y;
        int b=(a/1000)*((a/100)%10)*((a/10)%10)*(a%10);
        y=(b>200)?0:1;
        printf("%d\n",y);	
}
void main()
{
	int a;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	app70(a);
}
