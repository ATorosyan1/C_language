#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double app17(double a,double z)
{
	double y;
	if(abs(a)>3){
		y=pow((log(4+pow(a,2))/log(2)),5)+tan(z+a);
	}
	else
		y=pow((pow(z,4)+4*a),5);
	return y;
}
void main()
{
	double a,z;
	double y;	
	
	printf("a:");
	scanf("%lf",&a);
	printf("\n");

	printf("z:");
	scanf("%lf",&z);
	printf("\n");	
	
	y=app17(a,z);
	printf("y:%f\n",y);
}
