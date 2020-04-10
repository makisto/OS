#include <windows.h>
#include <stdio.h>

int main()
{
	system("CLS");
	
	SYSTEM_INFO siSysInfo;
	MEMORYSTATUS memStatus;
	
	char buffer[5];
	char WinDir[MAX_COMPUTERNAME_LENGTH + 1];
	char TempDir[100];
	wchar_t buf[256];
	
	int size = sizeof(buffer);
	int WinSize = sizeof(WinDir);
	int TempSize = sizeof(TempDir);

    GetSystemInfo(&siSysInfo); 
    GlobalMemoryStatus(&memStatus); 
	
	/*if(!GetComputerName((LPTSTR)buffer, (LPDWORD)&size))
	{
		printf("System error code: %i\n", GetLastError());
		//FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
		//printf("System error code: %s\n", &buf);
		return -1;	
	}*/
	if(!GetWindowsDirectory((LPTSTR)WinDir, (UINT)WinSize))
	{
		printf("System error code: %i\n", GetLastError());
		return -1;
	}	
	fprintf(stdout, "Windows Directory is %s\n", WinDir);
			
	if(!GetTempPathA((DWORD)TempSize, (LPTSTR)TempDir))
	{
		printf("System error code: %i\n", GetLastError());
		return -1;
	}
	fprintf(stdout, "Temp Directory is %s\n\n", TempDir);
   	
	printf("Hardware information: \n");  
	printf("Number of processors: %u\n", siSysInfo.dwNumberOfProcessors); 
	printf("Processor type: %u\n", siSysInfo.dwProcessorType); 
	printf("Minimum application address: %lx\n", siSysInfo.lpMinimumApplicationAddress); 
	printf("Maximum application address: %lx\n\n", siSysInfo.lpMaximumApplicationAddress); 
		
	printf("Memory information: \n");  
	printf("Total PhysMemory: %u\n", memStatus.dwTotalPhys); 
	printf("Available PhysMemory: %u\n", memStatus.dwAvailPhys); 
	printf("Total VirtualMemory: %lx\n", memStatus.dwTotalVirtual); 
	printf("Available VirtualMemory: %lx\n", memStatus.dwAvailVirtual); 
	
	return 0;
}
