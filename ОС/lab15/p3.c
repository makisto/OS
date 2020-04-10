#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	FILE* fp = fopen("1.html", "w+");
	char buff[sizeof(fp)];
	fread(buff, sizeof(fp), sizeof(fp), fp);
	for(DWORD i = 0; i < sizeof(fp); i++)
	{
		printf("%c", buff[i]);
	}
	fclose(fp);
	
	return 0;
}
