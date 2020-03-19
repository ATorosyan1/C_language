#include <stdio.h>
#include <math.h>
void app64(int a)
{
	char y;
        y=((a%10+(a/10)%10)==5)?'s':'d';
        printf("%c\n",y);	
}
void main()
{
	int a;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	app64(a);
}
