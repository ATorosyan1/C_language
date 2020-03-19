//ln(e^x+1)+xorarmat(x^2+4)
#include <stdio.h>
#include <math.h>

double app4(double x){
	double result;
	result=log10((exp(x)+1))+pow((pow(x,2)+4),(1/3));
	return result;
}

void main()
{
	double x;
	double result;
	printf("x:");
	scanf("%lf",&x);
	printf("\n");	
	
	
	result=app4(x);
	printf("result:%f\n",result);
}

