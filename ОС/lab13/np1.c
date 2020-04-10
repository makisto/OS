#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	char buff[255];
	DWORD iBytesToRead = 255;
	DWORD iBytesToWrite;
	
	hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX,
	PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
	PIPE_UNLIMITED_INSTANCES, 4096, 4096, NMPWAIT_USE_DEFAULT_WAIT,
	NULL);
	
	if(hPipe == INVALID_HANDLE_VALUE)
	{
		printf("CreatePipe failed: error code %d\n", (int)GetLastError());
		return -1;
	}
	printf("Waiting for connect...\n"); 
	
	if((ConnectNamedPipe(hPipe, NULL)) == 0)
	{
		printf("client could not connect\n");
		return -1;
	}

	printf("Connected. Waiting for command...\n"); 	
	
	while(1)
	{
		ReadFile(hPipe, buff, 255, &iBytesToRead, NULL);
		if(!WriteFile(hPipe, buff, strlen(buff) + 1, &iBytesToWrite, NULL))
	    break;
	    if(!strcmp(buff, "exit"))
	    {
	    	printf("Client has reconnected\n");
	    	break;	
		}
	    printf("Client - %s\n", buff);
	}
	
	CloseHandle(hPipe);
}
