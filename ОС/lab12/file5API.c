#include <windows.h>
#include <stdio.h>
#define N 20

int main(int argc, char* argv[])
{
	HANDLE hFile, hFileMap;
	PBYTE pByte;
	char dummy;
	
	hFile = CreateFile("testmap.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Could not open file.");
	}
	
	hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, N, NULL);
	if (hFileMap == NULL)
	{
		printf("Could not create mapping file.");
	}
	
	pByte = (PBYTE)MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (pByte == NULL)
	{
		printf("Could not map file.");
	}
	
	for(int i = 0; i < N; i++)
	{
		printf("%c", pByte[i]);	
	}
	printf("\n");
	
	/*pByte[0] = pByte[2] - 0x20;
	dummy = pByte[1];
	pByte[1] = pByte[3];
	pByte[2] = pByte[4];
	pByte[3] = pByte[10];
	pByte[4] = dummy;*/
	
	dummy = pByte[3];
	pByte[3] = pByte[2];
	pByte[2] = dummy;
	pByte[4] = dummy;
	for(int i = N; i >= 9; i--)
	{
		pByte[i] = pByte[i - 4];
	}
	pByte[5] = ' ';
	pByte[6] = 'i';
	pByte[7] = 'z';
	pByte[8] = ' ';
	
	for(int i = 0; i < N; i++)
	{
		printf("%lx\t%c\n", (unsigned long)(pByte + i), *(pByte + i));	
	}
	
	UnmapViewOfFile(pByte);
	CloseHandle(hFile);
	return 0;
}
