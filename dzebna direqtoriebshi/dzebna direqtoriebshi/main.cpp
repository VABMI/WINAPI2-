#include <windows.h>
#include <stdio.h>

HFONT hfont_global;



//----------------------------------------------------------------




BOOL find_file_in_dir(wchar_r *path)
{
	HANDLE hf;
	WIN32_FIND_DATA ffdata;
	wchar_r srchpath[MAX_PATH];
	
}

//----------------------------------------------------------------
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{
	switch(message)
	{
		case WM_CREATE:
			CreateWindow("button","dzebna",WS_VISIBLE|WS_CHILD|WS_BORDER,0,0,70,20,hwnd,(HMENU)1,0,0);

		break;
		
		case WM_COMMAND:

		break;
		
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_MOUSEMOVE:
		
			break;
		case WM_RBUTTONDBLCLK:
		case WM_LBUTTONDBLCLK:

		break;

		case WM_PAINT:

		break;

		case WM_KEYDOWN:

		break;
	}
return DefWindowProc(hwnd,message,wparam,lparam);
}
//----------------------------------------------------------------

int __stdcall WinMain(HINSTANCE,HINSTANCE,char *,int)
 //int main()
{
HWND hwnd=0;
int X,Y,W,H;
ULONG style=0;

WNDCLASS wc;
ZeroMemory(&wc,sizeof(WNDCLASS));

wc.style=CS_DBLCLKS;
wc.lpfnWndProc=(WNDPROC)&window_main_function_chvenia;
wc.lpszClassName="12";
wc.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(200,200,200));
wc.hIcon=(HICON)LoadImage(0,"c:\\1.ico",IMAGE_ICON,16,16,LR_LOADFROMFILE);

	if(RegisterClass(&wc)==0)
	{
	MessageBox(hwnd,"RegisterClass error",0,0);
	return 1;
	}


//mtavari fanjara:
style=WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN;
X=10;Y=30;W=700;H=500;
hwnd=CreateWindow(wc.lpszClassName,"Main",style,X,Y,W,H,0,0,0,0);

	
MSG msg;
int s=1;
	while(s!=0)
	{
	s=GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
}