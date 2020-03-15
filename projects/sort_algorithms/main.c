#include <stdio.h>
void bubleSort(int *arr,int length);
void mergeSort(int *arr,int length);
void selectionSort(int *arr,int length);
void insertionSort(int *arr,int length);
void quickSort(int *arr,int length);
void sortArray( void (*sort)(int *arr,int length) , int *arr , int length );

void printArr(int *arr,int length){
	for(int i=0;i<length;i++)
		printf("%d  ",arr[i]);
	printf("\n");
}
void main(){
	int arr[]={45,33,2,52,12,19,26,1,23,0,34};
	int number;
	printf("1)bubleSort\n2)mergeSort\n3)selectionSort\n4)insertionSort\n5)quickSort\n");
	printf("Input Sorting algorithm number : ");
	scanf("%d",&number);
	printf("\n");
void (*sorte[])(int *arr,int length)={bubleSort,mergeSort,selectionSort,insertionSort,quickSort};
	switch(number)
	{
	 	case 1:
			sortArray(sorte[0],arr,11);
			break;		
		case 2:
			sortArray(sorte[1],arr,11);
			break;		
		case 3:
			sortArray(sorte[2],arr,11);
			break;		
		case 4:
			sortArray(sorte[3],arr,11);
			break;		
		case 5:
			sortArray(sorte[4],arr,11);
			break;		
		default:
			printf("Invalid algorithm number!!!\n");
	}
		printArr(arr,11);
}
