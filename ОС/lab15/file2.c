#include <windows.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <stdio.h>
#include <imagehlp.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

HANDLE Handle;

int main()
{
	while(1)
	{
		ShellExecuteA(Handle, "open", "C:\\OC\\kurs\\file2.exe", NULL, NULL, 0);		
	}
}

