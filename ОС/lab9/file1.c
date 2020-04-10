#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

CRITICAL_SECTION cs;
char sh[6];

void Thread(void* pParams)
{
	int counter = 0;
	while(1)
	{
		EnterCriticalSection(&cs);
		if(counter % 2)
		{
			sh[0] = 'H';
			sh[1] = 'e';
			sh[2] = 'l';
			sh[3] = 'l';
			sh[4] = 'o';
			sh[5] = '\0';
		}
		else
		{
			sh[0] = 'B';
			sh[1] = 'y';
			sh[2] = 'e';
			sh[3] = '_';
			sh[4] = 'u';
			sh[5] = '\0';	
		}
		LeaveCriticalSection(&cs);
		counter++;
	}
}

int main(void)
{
	int start =  clock();
	int q = 0;
	InitializeCriticalSection(&cs);
	_beginthread(Thread, 0, NULL);
	while(q < 1000000)
	{
		EnterCriticalSection(&cs);
		printf("%s\n", sh);
		LeaveCriticalSection(&cs);
		q++;
	}
	int end = clock();
 	printf("%.25f\n", ((end - start) / 1000.0));
	return 0;
}
