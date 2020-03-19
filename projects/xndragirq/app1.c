//(y+1)(x+(x^2+1)^6)sin(x^2-3)-tg(y))
#include <stdio.h>
#include <math.h>
double app1(double x,double y)
{
	double result;
	result=(y+1)*(x+pow((pow(x,2)+1),6)*sin(pow(x,2)-3)-tan(y));
	return result;
}
void main()
{
	double x,y;
	double result;
	printf("x:");
	scanf("%f",&x);
	printf("\n");	
	
	printf("y:");
	scanf("%f",&y);
	printf("\n");	
	
	result=app1(x,y);
	printf("result:%f\n",result);
}
