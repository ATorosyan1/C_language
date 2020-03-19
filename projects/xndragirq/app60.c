#include <stdio.h>
#include <math.h>
void app60(int t)
{
	int a=t/100,b=(t/10)%10,r=t%10;
        if(a-b>0)
        {
            if(a-b<a-r)
                printf("%d\t%d\t%d\n",a,b,r);
            else
            if(a-b>a-r && a-r>0)
                printf("%d\t%d\t%d\n",a,r,b);
            else
            if(a-b>a-r && a-r<0)
                printf("%d\t%d\t%d\n",r,a,b);
        }
        else {
            if (a - r < a - b)
                printf("%d\t%d\t%d\n",r,b,a);
            if (a - r > a - b && a - r < 0)
                printf("%d\t%d\t%d\n",b,r,a);
            else if (a - r > a - b && a - r > 0)
                printf("%d\t%d\t%d\n",b,a,r);
        }
}
void main()
{
	int a;
	printf("a:");
	scanf("%d",&a);
	printf("\n");	
	
	app60(a);
}
