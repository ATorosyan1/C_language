#include <stdio.h>
void sortArray( void (*sort)(int *arr,int length) , int *arr ,int length) {
	sort(arr,length);
}
