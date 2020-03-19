#include <stdio.h>
#include <math.h>
void app39(int a,int b,int c,int d)
{
	int tmp;
     
   	if (a > b) {
            tmp = a;
            a = b;
            b = tmp;
        }
        if (c > d) {
            tmp = c;
            c = d;
            d = tmp;
        }
        if (a > c) {
            tmp = a;
            a = c;
            c = tmp;
        }
        if (b > d) {
            tmp = b;
            b = d;
            d = tmp;
        }
        if (b > c) {
            tmp = b;
            b = c;
            c = tmp;
        }

        printf("%d\t%d\t%d\t%d\n",a, b, c ,d);
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
	
	app39(a,b,c,d);
}
