#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>


void *  timer_th(void * arg){
  int hour = 0;
  int min  = 0;
  int sec  = 0;
  printf("**************************************************************\n");
  while (1) {
    /* code */
    printf("\r\t\t\t %2d : %2d : %2d",hour,min,sec);
    fflush(stdout);
    sec++;
    sleep(1);
    if(sec == 59){
      sec = 0;
      ++min;
    }
    if(min == 59){
      min = 0;
      ++hour;
    }
    if(hour == 24){
      hour = 0;
      min = 0;
      sec = 0;
    }
  }
}
void * funk(void * arg){
  int x;
  printf("\n%s","x: " );
  pthread_detach(pthread_self());
  scanf("%d\n",&x);
  printf("\n");
}
int main(){
  pthread_t t1;
  pthread_create(&t1,NULL,funk,NULL);
  timer_th(NULL);
  return 0;
}
