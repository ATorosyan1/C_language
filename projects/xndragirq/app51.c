#include <stdio.h>
#include <math.h>
void app51(int a)
{
	char * t="false";
        if(a%10==((a/10)%10)+((a/100)%10))
            t="true";
        printf("%s\n",t);
}
void main()
{
	int a;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	app51(a);
}
