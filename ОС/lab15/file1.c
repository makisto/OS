#include <windows.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <stdio.h>
#include <imagehlp.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

SERVICE_STATUS wserv_testStatus;
SERVICE_STATUS_HANDLE wserv_testStatusHandle;
STARTUPINFO si;
PROCESS_INFORMATION pi;
HANDLE Handle;
		
void __stdcall CtrlHandler(DWORD Opcode)
{
	DWORD status;
	switch(Opcode)
	{
		case SERVICE_CONTROL_PAUSE:
			wserv_testStatus.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			wserv_testStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		case SERVICE_CONTROL_STOP:
			wserv_testStatus.dwWin32ExitCode = 0;
			wserv_testStatus.dwCurrentState = SERVICE_STOPPED;
			wserv_testStatus.dwCheckPoint = 0;
			wserv_testStatus.dwWaitHint = 0;
			if(!SetServiceStatus(wserv_testStatusHandle, &wserv_testStatus))
			{
				status = GetLastError();
			}
			return;
		default:
			break;
	}
	
	if(!SetServiceStatus(wserv_testStatusHandle, &wserv_testStatus))
	{
		status = GetLastError();
	}
	return;
}

void __stdcall wserv_testStart(DWORD argc, LPTSTR* argv)
{
	DWORD status;
	
	wserv_testStatus.dwServiceType = SERVICE_WIN32;
	wserv_testStatus.dwCurrentState = SERVICE_START_PENDING;
	wserv_testStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	wserv_testStatus.dwWin32ExitCode = 0;
	wserv_testStatus.dwServiceSpecificExitCode = 0;
	wserv_testStatus.dwCheckPoint = 0;
	wserv_testStatus.dwWaitHint = 0;
	
	wserv_testStatusHandle = RegisterServiceCtrlHandler(TEXT("wserv_test"), CtrlHandler);
	if(wserv_testStatusHandle == (SERVICE_STATUS_HANDLE)0)
	{
		return;
	}
	wserv_testStatus.dwCurrentState = SERVICE_RUNNING;
	wserv_testStatus.dwCheckPoint = 0;
	wserv_testStatus.dwWaitHint = 0;
	if(!SetServiceStatus(wserv_testStatusHandle, &wserv_testStatus))
	{
		status = GetLastError();
	}
	FILE* fp;
	SYSTEMTIME stSystemTime;
	while(wserv_testStatus.dwCurrentState != SERVICE_STOPPED)
	{
		if(wserv_testStatus.dwCurrentState != SERVICE_PAUSED)
		{
			memset(&si, 0, sizeof(si));
			si.cb = sizeof(si);
			si.dwFlags = STARTF_USESTDHANDLES;
			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
			si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
			CreateProcess(NULL, "C:\\OC\\kurs\\file2.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
			/*GetSystemTime(&stSystemTime);
			fp = fopen("C:\\Test\\serv_log.txt", "a");
			fprintf(fp, "%d:%d:%d\n", stSystemTime.wHour, stSystemTime.wMinute, stSystemTime.wSecond);
			fclose(fp);*/
		}
		Sleep(500000);
	}
	
	return;
}

void main(int argc, char *argv[])
{
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);	
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	SERVICE_TABLE_ENTRY DispatchTable[] = 
	{
		{TEXT("wserv_test"), wserv_testStart},
		{NULL, NULL}
	};
	
	StartServiceCtrlDispatcher(DispatchTable);
	
	if(argc > 1 && !stricmp(argv[1], "setup"))
	{
		char pname[1024];
		pname[0] = '"';
		GetModuleFileName(NULL, pname + 1, 1023);
		strcat(pname, "\"");
		SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE), svc;
		if(!scm)
		{
			printf("Can't open SCM\n");
			exit(1);
		}
		if(!(svc = CreateService(scm, "wserv_test", "wserv_test", SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
		pname, NULL, NULL, NULL, NULL, NULL)))
		{
			printf("Registration error!\n");
			exit(2);
		}
		printf("Succesfully registered\n");
		CloseServiceHandle(svc);
		CloseServiceHandle(scm);
		exit(0);
	}
	
	if(argc > 1 && !stricmp(argv[1], "delete"))
	{
		SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if(!scm)
		{
			printf("Can't open SCM\n");
			exit(1);
		}
		SC_HANDLE svc = OpenService(scm, "wserv_test", DELETE);
		if(!svc)
		{
			printf("Can't open SCM\n");
			exit(2);
		}
		if(!DeleteService(svc))
		{
			printf("Can't open SCM\n");
			exit(3);
		}
		printf("Can't open SCM\n");
		CloseServiceHandle(svc);
		CloseServiceHandle(scm);
		
		exit(0);
	}
}
