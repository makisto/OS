#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct spis
{  	
	char surname[20];
	int mark;
	struct spis *next; 
}*head = NULL, *tail = NULL;

void Add()
{
    int mark1;
    char sur[20];
    printf("Input\n");
    printf("Surname:");
    scanf("%s", &sur);
    printf("Mark:");
    scanf("%d", &mark1);
    struct spis *tmp = (struct spis*)malloc(sizeof(struct spis));
    strcpy(tmp -> surname, sur);
    tmp -> mark = mark1;
    tmp -> next = NULL;
    if(head != NULL)
    {
        tail -> next = tmp;
    }
    else
    {
		head = tmp;
    }
    tail = tmp;
}

void Add1(int a)
{
    int mark1;
    char sur[20];
    printf("Surname:");
    scanf("%s", &sur);
    printf("Mark:");
    scanf("%d", &mark1);
    struct spis *tmp = (struct spis*)malloc(sizeof(struct spis));
    strcpy(tmp -> surname, sur);
    tmp -> mark = mark1;
    tmp -> next = NULL;
    struct spis *ptr1 = head;
    struct spis *ptr2 = head -> next;
    while(a-- != 1)
    {
    	if(ptr1 == NULL || ptr2 == NULL)
    	{
    		break;
		}
		else
		{
			ptr1 = ptr1 -> next;
			ptr2 = ptr2 -> next;
		}
	}
	ptr1 -> next = tmp;
	tmp -> next = ptr2;
}

void print()
{
    struct spis *tmp = head; 
    if(tmp == NULL)
    {
    	printf("List is empty\n");
	}
	else
	{
		int i = 0;
		while(tmp != NULL)
	    {
	    	i++;
	        printf("%d\t%s\t%d\n", i, tmp -> surname,  tmp -> mark);
	        tmp = tmp -> next;
	    }	
	}
}

void del()
{
    struct spis *tmp = head; 
    while(head != NULL)
    {  
        head = head -> next;
        free(tmp);
        tmp = head;
    } 
	printf("List has been cleared!\n");
}

void del1()
{   
    int mark1;
    printf("Input number 2-5\n");
    scanf("%d", &mark1); 		
	struct spis *tmp = head;
	struct spis *ptr = head -> next; 
	if(head -> mark == mark1)
	{
		head = head -> next;
		free(tmp);
	}
	else
	{	
		while(tmp -> next != NULL)
		{
			if(ptr -> mark == mark1)
			{
				if(ptr == tail)
				{
					tail = tmp;
					tail -> next = NULL;
					free(ptr);
					break;
				}
				else
				{
					tmp -> next = ptr -> next;
					free(ptr);	
					break;
				}
			}
			else
			{
				tmp = tmp -> next;
				ptr = ptr -> next;
			}
		}
	}
}
		
int main()
{
	int n;
	do
	{
		system("CLS");
		printf("1-Check List\n2-Create the List\n3-Add in List\n4-Delete from List\n5-Clear List\n6-Save In File\n7-Exit\n");
		scanf("%d", &n);
		switch(n)
		{
			case 1:
				system("CLS");
				print();
				system("PAUSE");
				break;
			case 2:
				system("CLS");
				int q1;
				printf("Elements-");
				scanf("%d", &q1);
				while(q1--)
				{
					Add();
				}
				system("PAUSE");
				break;
			case 3:
				system("CLS");
				int k;
				printf("Element-");
				scanf("%d", &k);
				if(head == NULL)
				{
					break;
				}			
				Add1(k);
				system("PAUSE");
				break;
			case 4:
				system("CLS");
				int q;
				printf("Elements-");
				scanf("%d", &q);
				while(q--)
				{
					if(head == NULL)
					{
						break;
					}
					print();
					del1();
					system("CLS");
				}
				system("PAUSE");
				break;
			case 5:
				system("CLS");
				del();
				system("PAUSE");
				break;
			case 6:
				FILE *f = fopen("journal.txt", "wb+");
				struct spis *tmp = head;
				int i = 0;
				while(tmp != NULL)
				{
					i++;
					fprintf(f, "%d\t%s\t%d\n", i, tmp->surname, tmp->mark);
					tmp = tmp->next;
				}
				fclose(f);
				break;
			case 7:
				exit(0);
			default:
				break;
		}
	}while(n != 6);
	
    return 0;   
}
