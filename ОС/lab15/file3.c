#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <tlhelp32.h>
    
int main(int argc, char* argv[])
{
	int i, index, idarray[1000];
	HANDLE hSnap, hProcess, h1Process;
	while(1)
	{
		system("CLS");
	    i = 0;
	    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	    if (hSnap == NULL)
	    {
	        return 0;
	    }
	    PROCESSENTRY32 proc;            
	                 
	    if(Process32First(hSnap, &proc))
	    {    
			printf("               Name process       PID   Number process\n");
	        do
			{ 
				if(!proc.th32ProcessID)
				{
					continue;
				}
	            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, proc.th32ProcessID);            
	            printf("%25s%12d%", proc.szExeFile, proc.th32ProcessID);
	            idarray[i] = proc.th32ProcessID;  
				i++;
				printf("\t%12d\n", i);
	        }while(Process32Next(hSnap, &proc));
	    }               
		////////////////////////////////////////////////////////////////////////////KILL
	    scanf("%d",&index);
	    h1Process = OpenProcess (PROCESS_ALL_ACCESS, FALSE, /*idarray[index]*/index); 
	    TerminateProcess(h1Process, 0);
	    CloseHandle(h1Process);
	 ////////////////////////////////////////////////////////////////////////////// Second snapshot
	}

    return 0;
}
