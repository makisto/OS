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

	while(1)
	{
	    gets(buff);
	    if(!WriteFile(hPipe, buff, strlen(buff) + 1, &iBytesToWrite, NULL))
	      break;
	    if(!strcmp(buff, "exit"))
	      break;
	}
	  
	CloseHandle(hPipe);
	return 0;
}
