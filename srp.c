#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
int z = 0, i = 0, j = 0, c = 0;
char a[16], h1[20], stack[15], h2[10]; 
void check()
{
	strcpy(h1,"REDUCE TO E -> ");
	for(z=0;z<c;z++)
	{
		if(stack[z] == 'a')
		{
			printf("%sa", h1);
			stack[z] = 'E';
			stack[z + 1] = '\0';
			printf("\n$%s\t%s$\t", stack, a);
		}
	}
	for(z=0;z<c;z++)
	{
		if(stack[z] == '(' && stack[z + 1] == 'E' && stack[ z + 2] == ')')
		{
			printf("%s(E)", h1); 
			stack[z]='E';
			stack[z + 1]='\0';
			stack[z + 2]='\0';
			printf("\n$ %s\t %s$\t", stack, a); 
			i = i - 2;
		}
	}
	for(z=0;z<c;z++)
	{
		if(stack[z] == 'E' && stack[z + 1] == '*' && stack[ z + 2] == 'E')
		{
			printf("%sE*E", h1);
			stack[z] = 'E';
			stack[z + 1] = '\0';
			stack[z + 2] = '\0';
			printf("\n$ %s\t %s$\t", stack, a); 
			i = i - 2;
		}
	}
	for(z=0;z<c;z++)
	{
		if(stack[z] == 'E' && stack[z + 1] == '+' && stack[ z + 2] == 'E')
		{
			printf("%sE+E", h1);
			stack[z]='E';
			stack[z + 1]='\0';
			stack[z + 2]='\0';
			printf("\n$ %s\t %s$\t", stack, a); 
			i = i - 2;
		}
	}
	for(z=0;z<c;z++)
	{
		if(stack[z] == 'E' && stack[z + 1] == '-' && stack[ z + 2] == 'E')
		{
			printf("%sE-E", h1);
			stack[z]='E';
			stack[z + 1]='\0';
			stack[z + 2]='\0';
			printf("\n$ %s\t %s$\t", stack, a); 
			i = i - 2;
		}
	}
	for(z=0;z<c;z++)
	{
		if(stack[z] == 'E' && stack[z + 1] == '/' && stack[ z + 2] == 'E')
		{
			printf("%sE/E", h1);
			stack[z]='E';
			stack[z + 1]='\0';
			stack[z + 2]='\0';
			printf("\n$ %s\t %s$\t", stack, a); 
			i = i - 2;
		}
	}
	return ;
}
int main() 
{
	printf("GRAMMAR is -\nE->a \nE->E*E \nE->E+E \nE->E-E \nE->E/E \nE->(E)\n");
	printf("enter the string\n"); 
	gets(a);
	c=strlen(a); 
	strcpy(h2,"SHIFT");
	printf("\nstack \t input \t\t action"); 
	printf("\n$\t %s$\t", a);
	for(i = 0; j < c; i++,j++)
	{
		printf("%s", h2);
		stack[i] = a[j];
		stack[i + 1] = '\0';
		a[j]=' ';
		printf("\n$ %s\t %s$\t", stack, a); 
		check();
	}
	if(stack[0] == 'E' && stack[1] == '\0') 
		printf("Accept\n");
	else
		printf("Reject\n");
}

