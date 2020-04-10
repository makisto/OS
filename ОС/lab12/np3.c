#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	char buff[255];
	DWORD iBytesToWrite;
	
	hPipe = CreateFile(lpPipeName, GENERIC_READ | GENERIC_WRITE,
	0, NULL, OPEN_EXISTING, 0, NULL);

	do
	{
		gets(buff);
		WriteFile(hPipe, buff, strlen(buff), &iBytesToWrite, NULL);
	}while(getch() != 27);
	CloseHandle(hPipe);
}
