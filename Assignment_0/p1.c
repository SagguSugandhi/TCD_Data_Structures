#include <stdio.h>
int main()
{
	char name[100];
	int age;
	printf("Name >> ");
	scanf("%s", name);
	printf("Age >> ");
	scanf("%d", &age);
	printf("Hello %s (%d)", name, age);
	return(0);
}
