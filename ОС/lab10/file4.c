#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <pthread.h>

char sh[6];
pthread_mutex_t Mutex;
void Thread(void* pParams);

int main(void)
{   
	int q = 0;
    pthread_t thread_id;
	pthread_mutex_init(&Mutex, NULL);
	pthread_create(&thread_id, NULL, &Thread, NULL);
	while(q < 1000)
	{
		pthread_mutex_lock(&Mutex);
		printf("%s\n", sh);
		pthread_mutex_unlock(&Mutex);
		q++;
	}
	
	return 0;
}

void Thread(void* pParams)
{
	int counter = 0;
	while(1)
	{
		pthread_mutex_lock(&Mutex);
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
		pthread_mutex_unlock(&Mutex);
		counter++;
	}
	//return NULL;
}
