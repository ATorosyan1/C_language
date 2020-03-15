#include <stdio.h>
void bubleSort(int * arr,int length){
	printf("It is bubleSort!!!\n");
	for(int i=length-1;i>0;i--){
		for(int j=0;j<i;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp;			
			}		
		}	
	}
}

/*void main(){
	int arr[5]={2,4,1,7,5};
	bubleSort(arr,5);
	for(int i=0;i<5;i++)
		printf("%d\t",arr[i]);
}*/
