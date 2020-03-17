#include <stdio.h>
typedef struct
{
	char *name;
	int age;
} Person;
void push(Person person);
Person pop();
void printStack();
void add(Person person);
Person removep(int index);
void printList();
void main()
{
	Person p1={"Arman",22};
	Person p2={"Karen",12};
	Person p3={"Vardan",25};
	
	push(p1);
	push(p2);
	push(p3);

	printStack();

	Person ptr=pop();
	printf("Pop element:\nName:%s\tAge:%d\n\n",ptr.name,ptr.age);

	add(p1);
	add(p2);
	add(p3);
	
	printList();	

	ptr=removep(2);
	printf("Remove element:\nName:%s\tAge:%d\n",ptr.name,ptr.age);
}
