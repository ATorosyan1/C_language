#include <stdio.h>
#include <math.h>
double app11(double a,double b,double x)
{
	double y;
	if((pow(a,2)+pow(b,2))>5){
		y=3*exp(a-x)+(log10(pow(a,2)+pow(b,2)+5)/log10(3));
	}else if((pow(a,2)+pow(b,2))<1){
		y=pow(tan(a+b),4);
	}
	else
		y=-3;
	return y;
}
void main()
{
	double x,a,b;
	double y;
	printf("x:");
	scanf("%lf",&x);
	printf("\n");	
	
	printf("a:");
	scanf("%lf",&a);
	printf("\n");

	printf("b:");
	scanf("%lf",&b);
	printf("\n");	
	
	y=app11(a,b,x);
	printf("y:%f\n",y);
}
