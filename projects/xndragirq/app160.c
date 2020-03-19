#include <stdio.h>
#include <math.h>
void app160()
{ 
      int a;
      double b;
      short t=0;
      for(double i=100;i<=999;i++)
      {
          a =(int) sqrt(i * 16);
          b=sqrt(i * 16);
          if((double)a==b) {
              t=1;
              printf("%d\n",(int)i);
              break ;
          }

      }
      if(t==0)
          printf("Invalid number!!!\n");


}
	
void main()
{		
	app160();
}
