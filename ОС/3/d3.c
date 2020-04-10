#include <windows.h>
#include "resource3.h"

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    MSG msg;
    DialogBox( hInstance, (LPCTSTR)IDD_DLGTEST, NULL, (DLGPROC)DlgProc);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
    return msg.wParam;
}

LRESULT CALLBACK
DlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam ){
    int strText1;
    int strText2;
    int strText3;
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
            
            case IDC_BTN1:
            strText1 = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, FALSE);
            strText2 = GetDlgItemInt(hDlg, IDC_EDIT2, FALSE, FALSE);
            strText3 = strText1 + strText2;
            SetDlgItemInt (hDlg,IDC_EDIT3,strText3, FALSE);
            break;
            
            case IDC_BTN2:
            strText1 = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, FALSE);
            strText2 = GetDlgItemInt(hDlg, IDC_EDIT2, FALSE, FALSE);
            strText3 = strText1 - strText2;
            SetDlgItemInt (hDlg,IDC_EDIT3,strText3, FALSE);
            break;
            
            case IDC_BTN3:
            strText1 = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, FALSE);
            strText2 = GetDlgItemInt(hDlg, IDC_EDIT2, FALSE, FALSE);
            strText3 = strText1 * strText2;
            SetDlgItemInt (hDlg,IDC_EDIT3,strText3, FALSE);
            break;
            
            case IDC_BTN4:
            strText1 = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, FALSE);
            strText2 = GetDlgItemInt(hDlg, IDC_EDIT2, FALSE, FALSE);
            strText3 = strText1 / strText2;
            SetDlgItemInt (hDlg,IDC_EDIT3,strText3, FALSE);
            break;
            
            case IDC_BTN5:
            strText1 = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, FALSE);
            strText3 = strText1 * strText1;
            SetDlgItemInt (hDlg,IDC_EDIT3,strText3, FALSE);
            break;
        }
    break;
    default:
    return FALSE;
    }
}
