#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic1;
HINSTANCE hInst;
int WIDTH, HEIGHT,LEFT,TOP,RIGHT,BOTTOM,FIRST_CLICKX, FIRST_CLICKY,LAST_CLICKX, LAST_CLICKY;
UINT nStaticCounter = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0); // закрываем модальный диалог
        return TRUE;
        // WM_INITDIALOG - данное сообщение приходит после создания диалогового окна, но перед его отображением на экран
    case WM_LBUTTONDOWN:

        FIRST_CLICKX = LOWORD(lParam);
        FIRST_CLICKY = HIWORD(lParam);
        return TRUE;
    case WM_LBUTTONUP:
        LAST_CLICKX = LOWORD(lParam);
        LAST_CLICKY = HIWORD(lParam);

       

        LEFT = FIRST_CLICKX < LAST_CLICKX ? FIRST_CLICKX : LAST_CLICKX;
        RIGHT = LEFT == FIRST_CLICKX ? LAST_CLICKX : FIRST_CLICKX;
        TOP = FIRST_CLICKY < LAST_CLICKY ? FIRST_CLICKY : LAST_CLICKY;
        BOTTOM = TOP == FIRST_CLICKY ? LAST_CLICKY : FIRST_CLICKY;
        if (abs(TOP - BOTTOM) >= 10 && abs(RIGHT - LEFT) >= 10) {
            TCHAR szStaticText[20];
            nStaticCounter++;
            WIDTH = abs(RIGHT - LEFT);
            HEIGHT = abs(TOP - BOTTOM);
            hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
                LEFT, TOP, WIDTH, HEIGHT, hWnd, 0, hInst, 0);
            _stprintf_s(szStaticText, _T("%d"), nStaticCounter);
            SetWindowText(hStatic1, szStaticText);
        }
        else {
            MessageBox(hWnd, TEXT("Your rectangle is too small"), TEXT("ALERT"), 1);
        }
        return TRUE;
    }
	return FALSE;
}