#include <stdio.h>
#include <math.h>
void app23(int a,int b,int c)
{
	if(a==1 || b==1 || c==1)
		printf("true\n");
	else
		printf("false\n");
}
void main()
{
	int a,b,c;
	double result;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	printf("b:");
	scanf("%d",&b);
	printf("\n");

	printf("c:");
	scanf("%d",&c);
	printf("\n");	
	
	app23(a,b,c);
}
