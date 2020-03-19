#include <stdio.h>
#include <math.h>
void app35(int a,int b,int c,int d)
{
	if (a == b + c + d || b == a + c + d || c == a + b + d || d == a + b + c) {
            printf("true\n");
        }else{
            printf("false\n");
        }
}
void main()
{
	int a,b,c,d;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	printf("b:");
	scanf("%d",&b);
	printf("\n");

	printf("c:");
	scanf("%d",&c);
	printf("\n");	
	
	printf("d:");
	scanf("%d",&d);
	printf("\n");
	
	app35(a,b,c,d);
}
