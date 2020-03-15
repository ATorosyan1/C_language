#include <stdio.h>
void insertionSort(int *arr,int length){
	printf("It is insertionSort!!!\n");
	for(int i=0;i<length;i++){
		for(int j=0;j<=i;j++){
			if(arr[j]>arr[i]){
				int temp=arr[j];
				arr[j]=arr[i];
				arr[i]=temp;			
			}
		}
	}	
}
/*void main(){
	int arr[]={2,4,1,8,5,3};
	insertionSort(arr,6);
	for(int i=0;i<6;i++)
		printf("%d   ",arr[i]);
	printf("\n");
}*/
