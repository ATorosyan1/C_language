#include <stdio.h>
void selectionSort(int * arr,int length){
	printf("It is selectionSort!!!\n");
	int min,index;
	for(int i=0;i<length;i++){
		min=arr[i];
		index=i;
		for(int j=i;j<length;j++){
			if(arr[j]<min){
				min=arr[j];
				index=j;
			}
		}
		if(arr[i]>min){
			arr[index]=arr[i];
			arr[i]=min;
		}
	}
}
/*void main(){
	int arr[]={2,4,1,8,5,3};
	selectionSort(arr,6);
	for(int i=0;i<6;i++)
		printf("%d   ",arr[i]);
	printf("\n");
}*/
