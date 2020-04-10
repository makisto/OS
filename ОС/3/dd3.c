#include <windows.h>
#include "resource3.h"

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    MSG msg;
    DialogBox( hInstance, (LPCTSTR)IDD_D, NULL, (DLGPROC)DlgProc);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
    return msg.wParam;
}

LRESULT CALLBACK
DlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam ){
    switch (message){
        case WM_INITDIALOG:
        return TRUE;
        
        case WM_COMMAND:
        switch (LOWORD(wParam) ){
            case IDOK:
            PostQuitMessage(0);
            return TRUE;
            
            case IDCANCEL:
            PostQuitMessage(0);
            return TRUE;
             
        }
    break;
    default:
    return FALSE;
    }
}
