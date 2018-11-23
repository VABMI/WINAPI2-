#include <windows.h>
#include <stdio.h>

#include "stdafx.h"
HFONT hfont_global;



//----------------------------------------------------------------

DWORD WINAPI Thread_no_1( LPVOID bufer1 ) 
{
	char*bufer=(char*)bufer1;
	

		        int length=strlen((char*)bufer);
				char *number=(char*)malloc(length);//=bufer;
				strcpy(number,(char*)bufer);
			   int x=atoi(number);
			   char buf2[1000];
			   int i=3;

				for( i=3;i<=x;i+=2)
					{
						if(i%3!=0)
						{
							char *ff;
					
							char buffer[20];
							itoa(i,buffer,10);

							strcat(buf2,(char*)buffer);
							strcat(buf2,"\n\r");
						}
					}

				MessageBox(0,buf2,buf2,0);
				
				free(number);

	return 1; 
} 
//----------------------------------------------------------------
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{
	switch(message)
	{
		case WM_CREATE:
			{
				RECT r;
				CreateWindow("edit","Main",WS_CHILD|WS_BORDER|WS_VISIBLE,0,0,150,30,hwnd,(HMENU)1,0,0);

				CreateWindow("Button","gashveba",WS_CHILD|WS_BORDER|WS_VISIBLE,155,0,80,30,hwnd,(HMENU)2,0,0);
				GetClientRect(hwnd,&r);
				CreateWindow("edit","Main",WS_CHILD|WS_BORDER|WS_VISIBLE,0,50,r.right,r.bottom-55,hwnd,(HMENU)1,0,0);

			}
		break;
		
		case WM_COMMAND:
			{

				if(wparam==2)
				{
					char bufer[100];
					SendMessage(GetDlgItem(hwnd,1),WM_GETTEXT,100,(LPARAM)bufer);
					MessageBox(0,bufer,bufer,0);

					CreateThread(0,0,Thread_no_1,&bufer,0,0);

				}

			
			}
		break;
		
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_MOUSEMOVE:
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