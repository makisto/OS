#include <stdio.h>
#include <windows.h>
#include <process.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char *argv[] = {"C:\\Users\\ilja-\\Desktop\\help.bat", NULL};
		
	_spawnvp(_P_NOWAIT, argv[0], argv); //Процесс и программа выполняются синхронно
	//_spawnvp(_P_WAIT, argv[0], argv); //Процесс закончился - программа прдолжилась
	//_spawnvp(_P_OVERLAY, argv[0], argv); //Перекрытие дальнейшей основной программы	
	
	MessageBoxW(NULL, "Process", "Message", MB_OK);
	
	return 0;	
}
