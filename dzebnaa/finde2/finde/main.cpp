
#include "windows.h"
#include "string.h"
#include "stdio.h"
#include "struct.cpp"
#include "dzebna.cpp"

//--------------------------------------------------------------------------------------------

long __stdcall mainProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	switch(msg)
	{
		case WM_CREATE:
			{

				#include "Create.cpp"

			}
		break;
		
		case WM_COMMAND:
			if(wp==1)
			{
				search val1;
				val1.constval();
				GetWindowText(GetDlgItem(hwnd,2),val1.SadzebniFaili,100);
				GetWindowText(GetDlgItem(hwnd,15),val1.path,100);

				
				//find_file_in_dir(val1.path,val1.SadzebniFaili);
				CreateThread(0,0,find_file_in_dir,(void*)&val1,0,0);

				Sleep(10);
				
				//MessageBoxW(0,L"dzebna dasrulebulia",L"dzebna dasrulebulia",0);
			}
			break;

	}

	return DefWindowProc(hwnd,msg,wp,lp);
}
void main()
{
	WNDCLASS wc={0};
	wc.lpszClassName=L"search";
	wc.lpfnWndProc=&mainProc;
	if(RegisterClass(&wc)==0)
	{

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
