#include <stdio.h>
#define DATA_SIZE 1024
struct _data
{
	double x;
	double y;
	int index;
};

int main(int argc, char* argv[])
{
	struct _data Data[64];
	FILE* fp;	
	fp = fopen("test.dat", "rb");
	for(int j = 0; j < DATA_SIZE / 64; j++)
	{
		fseek(fp, 64 * j * sizeof(struct _data), SEEK_SET);
		fread(Data, sizeof(struct _data), 64, fp);
		for(int i = 0; i < 64; i++)
		{
			printf("%d\t%g\t%g\n", Data[i].index, Data[i].x, Data[i].y);
			getchar();
		}
	}
	fclose(fp);
	
	return 0;
}
