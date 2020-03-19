//4armat(x^2 +3armat(y^2 + 4))+(|x|+|y|)^10
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double app8(double x,double y){
	double result;
	result=pow((pow(x,2)+pow((pow(y,2)+4),(1/3))),(1/4))+pow((abs(x)+abs(y)),10);
	return result;
}

void main()
{
	double x,y;
	double result;
	printf("x:");
	scanf("%lf",&x);
	printf("\n");	
	
	printf("y:");
	scanf("%lf",&y);
	printf("\n");
	
	result=app8(x,y);
	printf("result:%f\n",result);
}

