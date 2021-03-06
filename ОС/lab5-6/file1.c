#include <windows.h>

LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HDC hdc;
RECT rt;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	LPCSTR lpszAppName = "CTemplate1";
	BOOL ret;
	wc.lpszClassName = lpszAppName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)Proc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if(!RegisterClass(&wc))
	{
		return 0;
	}
	hWnd = CreateWindow(lpszAppName, lpszAppName, WS_OVERLAPPEDWINDOW, 100, 100, 400, 200, NULL, NULL, hInstance, NULL);
	ret = RegisterHotKey(hWnd, 0xB001, MOD_CONTROL | MOD_ALT, "W");
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}
