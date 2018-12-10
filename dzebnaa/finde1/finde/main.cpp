
#include "windows.h"
#include "string.h"
#include "stdio.h"
#include "Struct.cpp"
#include "dzebna.cpp"

//--------------------------------------------------------------------------------------------

long __stdcall mainProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	switch(msg)
	{
		case WM_CREATE:
			{
			CreateWindow(L"edit",L"",WS_VISIBLE|WS_CHILD|WS_BORDER,120,0,160,20,hwnd,(HMENU)2,0,0);
			HWND combo=CreateWindow(L"combobox",L"ssss",WS_VISIBLE|WS_CHILD|WS_BORDER|CBS_DROPDOWN | CBS_HASSTRINGS | CBS_SIMPLE |WS_VSCROLL|CBS_HASSTRINGS,0,0,100,190,hwnd,(HMENU)15,0,0);
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"C:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"A:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"B:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"D:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"E:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"F:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"G:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"H:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"I:");
			CreateWindow(L"button",L"dzebna",WS_VISIBLE|WS_CHILD|WS_BORDER,280,0,70,20,hwnd,(HMENU)1,0,0);
			}
		break;
		
		case WM_COMMAND:
			if(wp==1)
			{
			//	 wchar_t *sea=(wchar_t*)malloc(1000);
				//GetWindowText(GetDlgItem(hwnd,2),sea,100);
			//	  wchar_t * combo=(wchar_t*)malloc(1000);
			//	GetWindowText(GetDlgItem(hwnd,15),combo,100);
				//find_file_in_dir((wchar_t*)combo,(wchar_t*)sea);
				search val1;

				val1.constval();
			
				GetWindowText(GetDlgItem(hwnd,2),val1.SadzebniFaili,100);
				GetWindowText(GetDlgItem(hwnd,15),val1.path,100);
			//	find_file_in_dir((search*)&val1);
				CreateThread(0,0,find_file_in_dir,(search*)&val1,0,0);
				Sleep(10);
				//system("pause");
				val1.dconstval();
			}
			break;

	}

	return DefWindowProc(hwnd,msg,wp,lp);
}
void main()
{
//find_file_in_dir(L"C:",L"vc100.idb");

WNDCLASS wc={0};
wc.lpszClassName=L"search";
wc.lpfnWndProc=&mainProc;
if(RegisterClass(&wc)==0){

	return ;

}
CreateWindow(wc.lpszClassName,L"search",WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW|WS_BORDER|WS_VISIBLE|WS_BORDER,0,0,600,500,0,0,0,0);

MSG msg={0};
while(GetMessage(&msg,0,0,0)!=0)
{

	TranslateMessage(&msg);
	DispatchMessage(&msg);

}
system("\n\npause");
}
