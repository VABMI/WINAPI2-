// transparent.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "transparent.h"


#include <windows.h>



HWND    g_hwndButton            = NULL;  
HWND       g_hwndButton1	=	NULL;
WNDPROC g_wndProcButtonOrigianl = NULL;   
BOOL    g_bSeeingMouse          = FALSE;


LRESULT CALLBACK edit (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT __stdcall WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_CREATE:
        {
           g_hwndButton= CreateWindow("BUTTON", "Btn", WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD, 100, 100, 95, 25, Hwnd, (HMENU)1, NULL, NULL);
			      g_wndProcButtonOrigianl = (WNDPROC)SetWindowLongPtr( g_hwndButton, GWLP_WNDPROC, (LONG_PTR)edit );
		}
        break;
        case WM_ERASEBKGND:
        {
            SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
            SetLayeredWindowAttributes(Hwnd, GetSysColor(COLOR_WINDOW), 0, LWA_COLORKEY);
        }
        return 1;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(Hwnd, Msg, wParam, lParam);
    }
    return 0;
}
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, int nCmdShow)
//int main()
{
    WNDCLASSEX FormClass;
    FormClass.cbSize        = sizeof(WNDCLASSEX);
    FormClass.style         = CS_DBLCLKS;
    FormClass.lpfnWndProc   = WindowProcedure;
    FormClass.cbClsExtra    = 0;
    FormClass.cbWndExtra    = 0;
    FormClass.hInstance     = GetModuleHandle(NULL);
    FormClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    FormClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    FormClass.hbrBackground = NULL;
    FormClass.lpszMenuName  = NULL;
    FormClass.lpszClassName = "Class";
    FormClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&FormClass);
    HWND hwnd = CreateWindowEx(WS_EX_LAYERED, "Class", "Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, GetModuleHandle(NULL), NULL);
    SetLayeredWindowAttributes(hwnd, 0, 0xFF, LWA_ALPHA);
    MSG Messages = {0};
    ShowWindow(hwnd, SW_SHOW);
    while(GetMessage(&Messages, NULL, 0, 0))
    {
        TranslateMessage(&Messages);
        DispatchMessage(&Messages);
    }
    return Messages.wParam;
}







































/*
#define WIN32_LEAN_AND_MEAN

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <windows.h>

LPCWSTR s_szWndClassName = L"Semi-Transparent Window";
LPCWSTR s_szFile = L"C:\\Users\\vakho1\\Desktop\\1200x900\\11.bmp";
HBITMAP s_hBitmap = NULL;





ATOM RegisterWndClass(HINSTANCE, LPCWSTR);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP LoadPicture(LPCWSTR);
BOOL DrawPicture(HDC, LPRECT);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;

	s_hBitmap = LoadPicture(L"C:\\Users\\vakho1\\Desktop\\1200x900\\11.bmp"); 

	RegisterWndClass(hInstance, s_szWndClassName);

	hWnd = CreateWindowEx( WS_EX_LAYERED ,
		s_szWndClassName, s_szWndClassName, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
		NULL, NULL, hInstance, NULL);
																							///ES_MULTILINE|WS_VSCROLL

 g_hwndButton=	CreateWindow(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_MULTILINE,0,0,350,450,hWnd,(HMENU)10,0,0);

		///g_wndProcButtonOrigianl = (WNDPROC)SetWindowLongPtr( g_hwndButton, GWLP_WNDPROC, (LONG_PTR)edit );

	g_hwndButton=CreateWindow(L"button",L"rrrrrr",WS_VISIBLE|WS_CHILD,390,0,50,50,hWnd,(HMENU)11,hInstance,0);


	//	



		// long wAttr = GetWindowLong(g_hwndButton, GWL_EXSTYLE);
  //  SetWindowLong(g_hwndButton, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
   // SetLayeredWindowAttributes(g_hwndButton, 0, 0, LWA_COLORKEY);

	if (hWnd != NULL)
	{
		SetLayeredWindowAttributes(hWnd,  0,  
				(255 * 100) / 100, LWA_ALPHA);

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (s_hBitmap != NULL)
		DeleteObject(s_hBitmap);

	return (int)msg.wParam;
}

ATOM RegisterWndClass(HINSTANCE hInstance, LPCWSTR lpszWndClassName)
{
	WNDCLASSEX wcex		= { 0 };
	wcex.cbSize		= sizeof(WNDCLASSEX);
	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc		= WndProc;
	wcex.hInstance		= hInstance;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= lpszWndClassName;
	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
	 WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch (message)
	{

		  case WM_ERASEBKGND:
        {
            SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
            SetLayeredWindowAttributes(hWnd, GetSysColor(COLOR_WINDOW), 0, LWA_COLORKEY);
        }

		break;


	case WM_COMMAND:

		if(wParam==11)
			SendMessage(GetDlgItem(hWnd,10),WM_SETTEXT,5,(LPARAM)"rrrrrrrrdasd");



		break;
		  case WM_CTLCOLOREDIT:
		{
			
		 HDC hdcStatic = (HDC) wParam;
		/// SetTextColor(hdcStatic, edittextferi);	 

		//COLORREF ff= GetBkColor(hdcStatic);
		SetBkColor(hdcStatic,RGB(55, 5, 25));
	
	   //  return (INT_PTR)CreateSolidBrush(RGB(255,32,79));
		
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		DrawPicture(hdc, &rect);
		EndPaint(hWnd, &ps);
		break;
	case	WM_DRAWITEM: {  
    LPDRAWITEMSTRUCT pDIS;
    pDIS = (LPDRAWITEMSTRUCT)lParam;
    RECT rc;

    SetTextColor(pDIS->hDC, RGB(200,10,60));
    SelectObject(pDIS->hDC, (HPEN)GetStockObject(NULL_PEN));
    SelectObject(pDIS->hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
    SetBkMode(pDIS->hDC, TRANSPARENT);
    // Start Drawing
    Rectangle(pDIS->hDC, 0, 0, pDIS->rcItem.right+1, pDIS->rcItem.bottom+1);
    DrawText(pDIS->hDC, L"ierugeiugeiugeiug", 10, &pDIS->rcItem, 0); 
	
    return 0;
}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HBITMAP LoadPicture(LPCWSTR lpszFileName)
{
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, lpszFileName,
	IMAGE_BITMAP, 0, 0, 				
	LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); 
    return hBitmap;
}

BOOL DrawPicture(HDC hDC, LPRECT lpRect)
{
	BITMAP bitmap;
	HDC hMemDC;
	HGDIOBJ hBitmapOld;
	if (s_hBitmap == NULL)
		return FALSE;
	GetObject(s_hBitmap, sizeof(BITMAP), &bitmap);
	hMemDC = CreateCompatibleDC(hDC);
	hBitmapOld = SelectObject(hMemDC, s_hBitmap);
	StretchBlt(hDC, 
		lpRect->left, lpRect->top, 
		lpRect->right - lpRect->left,
		lpRect->bottom - lpRect->top, 
		hMemDC, 
		0, 0, bitmap.bmWidth, bitmap. bmHeight, 
		SRCCOPY);
	SelectObject(hMemDC, hBitmapOld);
	DeleteDC(hMemDC);
	return TRUE;
}
*/

LRESULT CALLBACK edit (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
		PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	char name[100];
	   WNDPROC wpOld = (WNDPROC)GetWindowLongPtr(g_hwndButton, GWLP_USERDATA);
	   HWND hwnd1=GetParent(hwnd);
	   HWND USER=GetDlgItem(hwnd1,23);
	 switch( message )
    {


		  case WM_ERASEBKGND:
        {
            SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
            SetLayeredWindowAttributes(hwnd, GetSysColor(COLOR_WINDOW), 0, LWA_COLORKEY);
        }


		break;



	 case WM_MOUSEMOVE:

		// MessageBox(0,L"button",L"asada",0);

		 break;
	
		case WM_PAINT:
			 
		SetLayeredWindowAttributes(hwnd,  0,  
		(255 * 70) / 100, LWA_COLORKEY);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);
		 SetBkMode ((HDC)wParam, TRANSPARENT);
		//////// aqedan komentariiii
		 /*
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawPicture(hdc, &rect);
		EndPaint(hwnd, &ps);
		 SetBkColor(hdc,RGB(255,32,79));
	
		SetBkMode (HDc, TRANSPARENT);
		TextOut (HDc, 0, 0, L"Text", 4);
		ReleaseDC (hWnd, HDc);

*/
		///// aqamde
      break;


	  case WM_KEYDOWN:

			  	if(wParam==13)
				{
					
				
						//// gagzavna
						//MessageBox(0,L"button",L"asada",0);

				}
		
			   
	  break;

    }





    return CallWindowProc( g_wndProcButtonOrigianl, hwnd, message, wParam, lParam );
}

