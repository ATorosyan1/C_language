#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void app57(int a)
{
	char* y=malloc(sizeof(char *));
        int b=a/1000+(a/100)%10+(a/10)%10+a%10;
        y=(a==b*b)?"YES":"NO";
        printf("%s\n",y);
}
void main()
{
	int a;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	app57(a);
}
