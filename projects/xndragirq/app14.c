#include <stdio.h>
#include <math.h>
double app14(double a,double b)
{
	double y;
	if(a+b<3){
		y=pow(atan(a+b),4);
	}else if(a+b>5){
		y=pow((log10(a+b)/log10(8)),2);
	}
	else
		y=pow(a,15);
	return y;
}
void main()
{
	double a,b;
	double y;	
	
	printf("a:");
	scanf("%lf",&a);
	printf("\n");

	printf("b:");
	scanf("%lf",&b);
	printf("\n");	
	
	y=app14(a,b);
	printf("y:%f\n",y);
}
