#include <stdio.h>
#include <math.h>
#define pi 3.141592
#define DATA_SIZE 1024
struct _data
{
	double x;
	double y;
	int index;
};

int main(int argc, char* argv[])
{
	struct _data Data[DATA_SIZE];
	FILE* fp;
	for(int i = 0; i < DATA_SIZE; i++)
	{
		Data[i].index = i;
		Data[i].x = i * (2.0 * pi / DATA_SIZE);
		Data[i].y = sin(Data[i].x);
	}
	
	fp = fopen("test.dat", "wb");
	fwrite(Data, sizeof(struct _data), DATA_SIZE, fp);
	fclose(fp);
	
	return 0;
}
