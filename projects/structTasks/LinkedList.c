#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char * name;
	int age:7;
} Person;

struct Node
{
	Person person;
	struct Node *next;
};
struct Node *first;
int countl()
{
	struct Node *temp=first;
	int count=0;
	while(temp!=NULL){
			count++;
			temp=temp->next;
		}
	return count;	
}
void add(Person person)
{
	if(first==NULL){
		first=malloc( sizeof(struct Node*));
		first->person=person;
		first->next=NULL;
		return;
	}
	struct Node *ptr=first;
	while(ptr->next!=NULL){
		ptr=ptr->next;	
	}
	ptr->next=(struct Node *)malloc( sizeof(struct Node));
	ptr->next->person=person;
	ptr->next->next=NULL;
		
}
Person get(int index)
{
	int i=0;
	if(index<0 || index>countl()){
		printf("Invalid index!\n");
		Person p={NULL,0};
		return	p;
	}
	if(index==0){
		Person p=first->person;
		return p;
	}
	struct Node *temp=first;
	while(i+1!=index){
		i++;
		temp=temp->next;		
	}
	return temp->next->person;

	
}
Person removep(int index)
{
	int i=0;
	if(index<0 || index>countl()){
		printf("Invalid index!\n");
		Person p={NULL,0};
		return	p;
	}
	if(index==0){
		Person p=first->person;
		first=first->next;
		return p;
	}
	struct Node *temp=first;
	while(i+1!=index){
		i++;
		temp=temp->next;		
	}
	struct Node* ptr=temp->next;
	temp->next=ptr->next;
	return ptr->person;

	
}
void printList()
{
	printf("LinkedList\n");

	struct Node *temp=first;
		while(temp!=NULL){
			printf("Name:%s\tAge:%d\n",temp->person.name,temp->person.age);
			temp=temp->next;
		}
	printf("\n");
}
/*void main()
{
	Person per1={"arman",22};
	Person per2={"karen",23};
	Person per3={"narek",24};
	add(per1);
	add(per2);
	add(per3);
	printf("count:%d\n",count());
	print();
	Person p=get(1);
	printf("Name:%s\tAge:%d\n",p.name,p.age);
	//print();
	
}*/

