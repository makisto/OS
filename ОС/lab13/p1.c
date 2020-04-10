#include <windows.h>
#include <math.h>
#include <stdio.h>

int main()
{
	HANDLE hPipeIn, hPipeOut;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si, si1;
	PROCESS_INFORMATION pi, pi1;
	
	char buff[80];
	unsigned long dw;
	
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	
	if(!CreatePipe(&hPipeIn, &hPipeOut, &sa, 0))
	{
		printf("The pipe could not be created\n");
		exit(1);
	}
	
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hPipeIn;
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	
	memset(&si1, 0, sizeof(si1));
	si1.cb = sizeof(si1);
	si1.dwFlags = STARTF_USESTDHANDLES;
	si1.hStdInput = hPipeIn;
	si1.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si1.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	
	if(!CreateProcess(NULL, "p2.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		printf("Could not create process, %i\n", GetLastError());
		exit(1);
	}
	if(!CreateProcess(NULL, "p3.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1))
	{
		printf("Could not create process, %i\n", GetLastError());
		exit(1);
	}
	CloseHandle(hPipeIn);
	
	for(double x = 0.0; x < 3.1416; x += 0.1)
	{
		sprintf(buff, "%g   %g\n", x, sin(x));
		WriteFile(hPipeOut, buff, strlen(buff), &dw, NULL);
	}
	
	*buff = (char)26;
	WriteFile(hPipeOut, buff, 1, &dw, NULL);
	
	CloseHandle(hPipeOut);
	
	return 0;
}
