#include <stdio.h>
#include <math.h>
void app169(int y)
{ 
	int x=1,z,temp=2;
        while((x+y)%temp!=0)
            temp++;
        z=temp==(x+y)?5:6;
        printf("z=%d\n",z);
}
	
void main()
{		
	app169(69);
}
