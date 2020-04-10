#include <windows.h>
#include <stdio.h>
#include <conio.h>

int q = 0;

int g(char* str, int* p)
{
	return 0;
}

DWORD WINAPI Thread(void* pg)
{
	//q++;
	for(int i = 0; i < 10; i++)
	{
		q++;
		Sleep(100);
	}
	return 0;
}

int main(void)
{
	srand(time(NULL));
	DWORD dwThreadId;
	/*while(q < 1000)
	{*/
		//printf("Next\n");
		for(int i = 0; i < 100; i++)
		{
			CreateThread(NULL, 0, Thread, g, 0, &dwThreadId);
			//Sleep(10);
			//printf("%d\n", q);
			//printf("%d\n", dwThreadId);	
		}	
	//}	
	getch();
	printf("%d\n", q);
	return 0;
}
