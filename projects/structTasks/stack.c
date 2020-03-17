#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	char *name;
	int age;
} Person;

Person *persons;
int length;
int index=0;
void push(Person person)
{
	if(persons == NULL){
		printf("Input persons max count : ");
		scanf("%d",&length);
		printf("\n");
		persons=calloc(length,sizeof(Person));
	}
	if(index>=length){
		printf("Stack is full!!!\n");
		return;
	}
	persons[index++]=person;
		
}
Person pop()
{
	if(index==0){
		printf("Stac is empty!!!\n");
		Person q={NULL,0};
		return q;	
	}
	Person p =persons[--index];
	Person q={NULL,0};
	persons[index] = q;
	return p;	
}
Person peek()
{
	if(index==0){
		printf("Stac is empty!!!\n");
		Person q={NULL,0};
		return q;		
	}
	return persons[index-1];
}
int count(){
	return index;
}
void printStack()
{
	printf("Stack\n");
	for(int i=index-1;i>=0;i--)
		printf("Name:%s\tAge:%d\n",persons[i].name,persons[i].age);
	printf("\n");
}
/*void main()
{
	Person per1={"arman1",21};
	Person per2={"arman2",22};
	Person per3={"arman3",23};
	Person per4={"arman4",24};
	Person per5={"arman5",25};
	push(per1);
	push(per2);
	push(per3);
	push(per4);
	push(per5);
	Person q=pop();
	printf("%s\t%d\n",q.name,q.age);
	q=peek();
	printf("%s\t%d\n",q.name,q.age);
	printf("count :%d\n",count());
	
}*/

