#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	FILE* fp = fopen("1.html", "r+");
	char buff[1015];
	fread(buff, sizeof(fp), 1015, fp);
	for(DWORD i = 0; i < 1015; i++)
	{
		printf("%c", buff[i]);
	}
	fclose(fp);
	
	return 0;
}
