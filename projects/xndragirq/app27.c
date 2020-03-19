#include <stdio.h>
#include <math.h>
void app27(int a,int b,int c)
{
	if((b-a)==(c-b))
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
	
	app27(a,b,c);
}
