#include <stdio.h>
#include <stdlib.h>
#define tes(s) printf("parametr = %d\n",s);
extern int d;
int qar()
{
	static int x=2;
	return x<<=1;
}
void main()
{
	int ** arr;
	int syun;
	int qanak;
	printf(" syuner: ");
	scanf("%d",&syun);
	printf("\n");
	arr=calloc(syun,sizeof(int*));
	for(int i=0;i<syun;i++){
		printf("tareri qanak@ arr[%d]:",i);
		scanf("%d",&qanak);
		printf("\n");
		arr[i]=malloc(qanak*sizeof(int));
		for(int j=0;j<qanak;j++){
			printf("arr[%d][%d]=",i,j);
			scanf("%d",&arr[i][j]);
			printf("\n");		
		}
	}
	for(int i=0;i<syun;i++){
		for(int j=0;j<sizeof(arr)/sizeof(arr[0]);j++){
			printf("%d",arr[i][j]);	
			printf(" , ");	
		}
		printf("\n");
	}
}
