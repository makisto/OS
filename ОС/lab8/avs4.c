#include <stdio.h>
#include <time.h>

const int a = 2;

int main()
{
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	int x[n], y[n];
	for(int i = 0; i < n; i++)
	{
		x[i] = rand();
		y[i] = rand();	
	}
	for(int i = 0; i < n; i++)
	{
		printf("%d ", y[i]);	
	}
	printf("\n");
	for(int i = 0; i < n; i++)
	{
		printf("%d ", y[i]);	
	}		
}
