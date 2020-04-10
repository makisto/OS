#include <windows.h>

HDC hdc;
RECT rt;
HWND hWnd, hwnd, hWndB1, hWndB2, hWndB3, hWndB4, hWndTB;
int result = 0;

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{					
	PAINTSTRUCT ps;
	COPYDATASTRUCT data;
	char buffer[8];
	char x[8];
	char *p;
	int res1;
	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			if(wParam == 100)
			{
				GetWindowText(hWndTB, x, 8);
				res1 = atoi(x);
				result += res1;
				p = itoa(result, buffer, 10);
				data.cbData = sizeof(buffer);
				data.lpData = p;
				SendMessage(hwnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);	
			}
			if(wParam == 101)
			{	
				GetWindowText(hWndTB, x, 8);
				res1 = atoi(x);
				result -= res1;
				p = itoa(result, buffer, 10);
				data.cbData = sizeof(buffer);
				data.lpData = p;
				SendMessage(hwnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);	
			}
			if(wParam == 102)
			{	
				GetWindowText(hWndTB, x, 8);
				res1 = atoi(x);
				result /= res1;
				p = itoa(result, buffer, 10);
				data.cbData = sizeof(buffer);
				data.lpData = p;
				SendMessage(hwnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);		
			}
			if(wParam == 103)
			{
				GetWindowText(hWndTB, x, 8);
				res1 = atoi(x);
				result *= res1;
				p = itoa(result, buffer, 10);
				data.cbData = sizeof(buffer);
				data.lpData = p;
				SendMessage(hwnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);			
			}
			break;
		case WM_COPYDATA:
			GetClientRect(hwnd, &rt);
			hdc = GetDC(hwnd);
			
			DrawText(hdc, "                                     ", 35, &rt, DT_CENTER);
			DrawText(hdc, (char*)(
			((COPYDATASTRUCT*)lParam)->lpData), 
			((COPYDATASTRUCT*)lParam)->cbData, &rt, 
			DT_CENTER);
			
			ReleaseDC(hWnd, hdc);
			break;
			
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);			
	}
}

LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{					
	PAINTSTRUCT ps;
	COPYDATASTRUCT data;

	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COPYDATA:
			GetClientRect(hWnd, &rt);
			hdc = GetDC(hWnd);
			
			DrawText(hdc, "                                     ", 35, &rt, DT_CENTER);
			DrawText(hdc, (char*)(
			((COPYDATASTRUCT*)lParam)->lpData), 
			((COPYDATASTRUCT*)lParam)->cbData, &rt, 
			DT_CENTER);
			
			ReleaseDC(hWnd, hdc);
			break;
			
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);			
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	WNDCLASS wc, wp;
	LPCSTR lpszAppName = "Калькулятор";
	
	wc.lpszClassName = lpszAppName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)MyWndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	
	wp.lpszClassName = lpszAppName;
	wp.hInstance = hInstance;
	wp.lpfnWndProc = (WNDPROC)Proc;
	wp.hCursor = LoadCursor(NULL, IDC_ARROW);
	wp.hIcon = 0;
	wp.lpszMenuName = 0;
	wp.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wp.style = CS_HREDRAW | CS_VREDRAW;
	wp.cbClsExtra = 0;
	wp.cbWndExtra = 0;
		
	if(!RegisterClass(&wc))
	{
		return 0;
	}
	
	hwnd = CreateWindow(lpszAppName, lpszAppName, WS_OVERLAPPEDWINDOW, 100, 100, 400, 200, NULL, NULL, hInstance, NULL);
	hWnd = CreateWindow(lpszAppName, lpszAppName, WS_OVERLAPPEDWINDOW, 100, 100, 400, 200, NULL, NULL, hInstance, NULL);
	hWndB1 = CreateWindow("BUTTON", "+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 220, 50, 32, 32, hWnd, (HMENU)100, hInstance, NULL);
	hWndB2 = CreateWindow("BUTTON", "-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 190, 50, 32, 32, hWnd, (HMENU)101, hInstance, NULL);
	hWndB3 = CreateWindow("BUTTON", "/", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 160, 50, 32, 32, hWnd, (HMENU)102, hInstance, NULL);
	hWndB4 = CreateWindow("BUTTON", "*", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 130, 50, 32, 32, hWnd, (HMENU)103, hInstance, NULL);
	hWndTB = CreateWindow("EDIT", " ", WS_BORDER | WS_VISIBLE | WS_CHILD , 150, 90, 100, 25, hWnd, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	ShowWindow(hwnd, SW_SHOW);
	
	UpdateWindow(hWnd);
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}
