#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int readyFlags[2];
int turn;
char sh[6];
int counter = 0;

void EnterCriticalRegion(int threadId)
{
	readyFlags[threadId] = 1;
	turn = 1 - threadId;
	while(turn == 1 - threadId && readyFlags[1 - threadId]);
}

void LeaveCriticalRegion(int threadId)
{
	readyFlags[threadId] = 0;
}

void thread()
{
	while(counter < 1000000)
	{
		EnterCriticalRegion(0);
		if(counter % 2 == 0)
		{
			sh[0] = 'H';
			sh[1] = 'e';
			sh[2] = 'l';
			sh[3] = 'l';
			sh[4] = 'o';
			sh[5] = '\0';
		}
		//printf("%s\n", sh);
		LeaveCriticalRegion(0);
		counter++;
	}
	readyFlags[0] = 0;			 
}

void thread1()
{
	while(counter < 1000000)
	{
		EnterCriticalRegion(1);
		if(counter % 2 == 1)
		{
			sh[0] = 'B';
			sh[1] = 'y';
			sh[2] = 'e';
			sh[3] = '_';
			sh[4] = 'u';
			sh[5] = '\0';
		}
		//printf("%s\n", sh);
		LeaveCriticalRegion(1);
		counter++;
	}	
	readyFlags[1] = 0;				 
}

int main(void)
{
	int start =  clock();
	int q = 0;
	HANDLE h[2];
	h[0] = (HANDLE)_beginthread((void*)thread, 0, NULL);
	h[1] = (HANDLE)_beginthread((void*)thread1, 0, NULL);
	
	WaitForMultipleObjects(2, h, TRUE, INFINITE);
	int end = clock();
 	printf("%.25f\n", ((end - start) / 1000.0));
	return 0;
}
