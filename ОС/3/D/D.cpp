#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define ID_EDIT 100
#define ID_BUTTON 101
#define ID_BUTTON_C 102

HINSTANCE hInst;
TCHAR buf[256];
HWND Wnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//void WINAPI MyDisplay( LPSTR, LPSTR, DWORD );

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hWnd;
	static TCHAR szWindowsClass[] = _T("Client");

 	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWindowsClass;


	if(!RegisterClass(&wc))
		return 0;

 hWnd = CreateWindow(szWindowsClass,
						szWindowsClass,
						WS_OVERLAPPEDWINDOW,
						100,
						100,
						400,
						300,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	

	////////////////////

	MSG message;

	while(GetMessage(&message,NULL,0,0)){
		Wnd = FindWindow(_T("Sender"), _T("Sender"));
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static HWND hEdit, hButton, hButton_C;
	LPSTR k;
	COPYDATASTRUCT data;
	PCOPYDATASTRUCT D;
					
	switch(message){
		case WM_CREATE:
			hEdit = CreateWindow(("edit"), (""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 30, 80, 300, 35, hWnd, (HMENU)ID_EDIT, hInst, 0);
			hButton = CreateWindow(("Button"), ("Send"), WS_CHILD | WS_VISIBLE  | BS_PUSHBUTTON, 100, 150, 50, 35, hWnd, (HMENU)ID_BUTTON, hInst, 0);
			hButton_C = CreateWindow(("Button"), ("Clear"), WS_CHILD | WS_VISIBLE  | BS_PUSHBUTTON, 200, 150, 50, 35, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);

			
			
            //if (Wnd) EnableWindow(hButton, TRUE);
			//else EnableWindow(hButton, FALSE);


			break;
		case WM_COPYDATA:
			buf[0] = 0;
			SetWindowText(hEdit, buf);
			D = (PCOPYDATASTRUCT) lParam;
			k = (LPSTR) (D->lpData);
            strcat(buf, TEXT(k));
            SetWindowText(hEdit, buf);
  			break;	
		case WM_DESTROY:
      		PostQuitMessage(0);
      		break;
      		
       
		case WM_COMMAND:
			if((LOWORD(wParam)==ID_BUTTON)&&(HIWORD(wParam)==BN_CLICKED))
            {
			 	GetWindowText(hEdit, buf, sizeof(buf));
			
				data.cbData = strlen(buf);
				data.lpData=buf;
				SendMessage(Wnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);
				

            }
			if((LOWORD(wParam)==ID_BUTTON_C)&&(HIWORD(wParam)==BN_CLICKED))
            {
			    buf[0] = 0;
				SetWindowText(hEdit, buf);
            }
		
		default:
			return DefWindowProc(hWnd,message,wParam,lParam);
			break;
	}
	return 0;
}

