#include <stdio.h>
#include <math.h>
void app31(int a,int b,int c,int d)
{
	if (a > b && a > c && b > d) {
            printf("%d\t",a);
        }else if (b > c && b > d){
             printf("%d\t",b);
        }else if (c > d) {
             printf("%d\t",c);
        }else{
            printf("%d\t",d);
        }
	printf("\n");
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
	
	app31(a,b,c,d);
}
