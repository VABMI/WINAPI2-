#include "head.h"
HFONT hfont_global;
SOCKET sock; ////soketi g
HBITMAP hBitmap01;
#include"myfunc.cpp"
#include"Procedura.cpp"
#include "mouse_msg.cpp"
#include "kbd_msg.cpp"
#include "cmd_msg.cpp"
#include "paint.cpp"
#include "on_create.cpp"


BOOL DrawPicture(HDC hDC, LPRECT lpRect);
HBITMAP LoadPicture(LPCSTR lpszFileName);
//----------------------------------------------------------------

//----------------------------------------------------------------
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{

	
			if(WM_USER+200==wparam)
			{


					/////////////////////////////////////////////////////////////////////////
						HMENU hMenu = ::CreateMenu();
						HMENU hmenu_popup_file=CreatePopupMenu();


							if (NULL != hMenu)
							{
								::AppendMenu(hmenu_popup_file, MF_STRING, 1, "Item 1");
								::AppendMenu(hmenu_popup_file, MF_STRING, 2, "Item 2");
								::AppendMenu(hmenu_popup_file, MF_STRING, 3, "Item 3");
							}
						////////////////////////////////////////////////////////////////////////
					LPNMITEMACTIVATE	 lpnmitem = (LPNMITEMACTIVATE) lparam;



					char fgr[100];
				///	sprintf(fgr,"%d",lpnmitem->iItem);
				//	MessageBox(hwnd,fgr,"Asdas",0);

					if(lpnmitem->iItem!=-1)
					{
					::TrackPopupMenuEx(hmenu_popup_file, TPM_CENTERALIGN | TPM_RETURNCMD,lpnmitem->ptAction.x,lpnmitem->ptAction.y+100,GetDlgItem(hwnd,369),NULL);
					
					
					
					
					//MessageBox(hwnd,"Asdad","asdasd",0);
					}

			}


if ( message==WM_USER+200)
  {
	  if(LOWORD(lparam)==WM_RBUTTONDOWN)
	  {
  		
					/////////////////////////////////////////////////////////////////////////
						HMENU hMenu = ::CreateMenu();
						HMENU hmenu_popup_file=CreatePopupMenu();


							if (NULL != hMenu)
							{
								::AppendMenu(hmenu_popup_file, MF_STRING, 1, "Item 1");
								::AppendMenu(hmenu_popup_file, MF_STRING, 2, "Item 2");
								AppendMenu(hmenu_popup_file, MF_STRING, 3, "Item 3");
								if(AppendMenu(hmenu_popup_file, MF_STRING, 3, "Item 3"))	
								{
									::TrackPopupMenuEx(hmenu_popup_file, TPM_CENTERALIGN | TPM_RETURNCMD,1090,700,hwnd,NULL);

								}
							}
						////////////////////////////////////////////////////////////////////////
						//	LPNMITEMACTIVATE	 lpnmitem = (LPNMITEMACTIVATE) lparam;



					char fgr[100];
					///sprintf(fgr,"%d",lpnmitem->iItem);
				//	MessageBox(hwnd,fgr,"Asdas",0);

				//	if(lpnmitem->iItem!=-1)
				


	  }

  }



	switch(message)
	{


		

		#include "Wm_notify.cpp"


		break;
		case WM_CREATE:
			{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			  // handle to icon
				 HBITMAP hIcon;
			  // text for tool tip
				 char lpszTip[] = "Mouse is on the Icon !!";
 
			//	 HINSTANCE hInst =
				//	 AfxFindResourceHandle(MAKEINTRESOURCE(IDI_ICON1),RT_GROUP_ICON);

				 hIcon = (HBITMAP)LoadImage( NULL,
										   "D:\\WINAPI1-\\icon\\Debug\\Itzikgur-My-Seven-Downloads-2.ico",
										   IMAGE_ICON,
										   16,
										   16,
										   LR_LOADFROMFILE);





			///	 (HBITMAP)LoadImage(NULL,"C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\MARBLES.BMP", IMAGE_BITMAP,300,300, LR_LOADFROMFILE);
				 if(hIcon)
				 {
    
					  // set NOTIFYCONDATA structure
 
						 NOTIFYICONDATA tnid;
 
						 tnid.cbSize = sizeof(NOTIFYICONDATA);
						 tnid.hWnd = hwnd;
						 tnid.uID = 0;
						 tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
						 tnid.uCallbackMessage = WM_USER+200; // my user message
						 tnid.hIcon =(HICON) hIcon;
						
						 if (lpszTip)
							lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip));
						 else
							tnid.szTip[0] = '\0';
 
					  // call to Shell_NotifyIcon with NIM_ADD parameter
 
						 Shell_NotifyIcon(NIM_ADD, &tnid);
 
					  // free icon 
 
						 ///if (hIcon) 
					//	 DestroyIcon(hIcon); 
				 }
			

				//////////////////////////////////////////////////////////////////////////////////
				RECT r;
				GetClientRect(GetDesktopWindow(),&r);
				int X=r.right-350,Y=0,W=350,H=r.bottom-40;
				hBitmap01 = (HBITMAP)LoadImage(NULL, "11.bmp", IMAGE_BITMAP, W,H, LR_LOADFROMFILE);
				on_create(hwnd,message,wparam,lparam);
			}
		break;
		
		case WM_COMMAND:


		on_cmd(hwnd,message,wparam,lparam);
		break;
		
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
//		case WM_MOUSEMOVE:
		case WM_RBUTTONDBLCLK:
		case WM_LBUTTONDBLCLK:
	//	on_mouse(hwnd,message,wparam,lparam);
		break;
	case WM_CTLCOLOREDIT:
{
	// HDC hdcStatic = (HDC) wparam;
		//SetTextColor((HDC) wparam, RGB(55, 55, 255)); //White text
  //Set the brush origin (relative placement)
		//SetBkColor(hdcStatic,RGB(55, 5, 25));
}

		case WM_PAINT:
			{
				/*
					PAINTSTRUCT ps;
					HDC hdc;
					RECT rect;
							*/	
					PAINTSTRUCT     ps01,ps;
			HDC             hdc01;
			BITMAP          bitmap01;
			HDC             hdcMem01;
			HGDIOBJ         oldBitmap01;

			hdc01 = BeginPaint(hwnd, &ps01);

			hdcMem01 = CreateCompatibleDC(hdc01);
			oldBitmap01 = SelectObject(hdcMem01, hBitmap01);

			GetObject(hBitmap01, sizeof(bitmap01), &bitmap01);
			BitBlt(hdc01, 0, 0, bitmap01.bmWidth, bitmap01.bmHeight, hdcMem01, 0, 0, SRCCOPY);

			SelectObject(hdcMem01, oldBitmap01);
			DeleteDC(hdcMem01);

			EndPaint(hwnd, &ps01);
			
					/*
			hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawPicture(hdc, &rect);
		EndPaint(hwnd, &ps);
		*/
			}
   break;
		break;
		case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO lpMMI = (LPMINMAXINFO)lparam;
		//	lpMMI->ptMinTrackSize.x = 1336-350;
		//	lpMMI->ptMinTrackSize.y = 728;
		}
		case WM_KEYDOWN:
		on_kbd(hwnd,message,wparam,lparam);
		break;
		
		case WM_HSCROLL:
		{

				HWND hg=(HWND)lparam;
		
				if(GetWindowLong(hg,-12)==24)
				{
					int gf=SendMessage(hg,TBM_GETPOS,0,0);

				SetLayeredWindowAttributes(hwnd,  0,  
				(255 * gf) / 100, LWA_ALPHA);

				ShowWindow(hwnd, SW_SHOWNORMAL);
					//UpdateWindow(hwnd);
					//MessageBox(0,"yu",0,0);
				}


		}

		break;
		case WM_CLOSE://default:
			WSACleanup();
			exit(1);
			break;
	}
return DefWindowProc(hwnd,message,wparam,lparam);
}
//----------------------------------------------------------------

//int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
	
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, int nCmdShow)

 //int main()
{
	HWND hwnd=0;
	int X,Y,W,H;
	ULONG style=0;
	s_hBitmap = LoadPicture("11.bmp"); 

	WNDCLASSEX wcex		= { 0 };
	wcex.cbSize		= sizeof(WNDCLASSEX);
	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc		= window_main_function_chvenia;
	wcex.hInstance		= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "12";
	if(RegisterClassEx(&wcex)==0)
	{
	MessageBox(hwnd,"RegisterClass error",0,0);
	return 1;
	}


//mtavari fanjara:
style=WS_VISIBLE |WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW;
/*
WS_OVERLAPPED 
WS_CAPTION    
WS_SYSMENU    
WS_THICKFRAME 
WS_MINIMIZEBOX
WS_MAXIMIZEBOX
*/

CreateTrackbar(hwnd,0,200,10,50,10,50,1,TBS_HORZ,800,30);
RECT r;
GetClientRect(GetDesktopWindow(),&r);
X=r.right-350;Y=0;W=350;H=r.bottom-40;
hwnd=CreateWindowEx(WS_EX_LAYERED,wcex.lpszClassName,"Main",WS_POPUP|WS_CLIPCHILDREN|WS_VISIBLE,X,Y,W,H,0,0,hInstance,0);
HwndParent=hwnd;
			SetLayeredWindowAttributes(hwnd,  0,  
				(255 * 100) / 100, LWA_ALPHA);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);
		SocketisSheqmna(hwnd);



MSG msg;
int s=1;
	while(s!=0)
	{
	s=GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
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


HBITMAP LoadPicture(LPCSTR lpszFileName)
{
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, lpszFileName,
	IMAGE_BITMAP, 0, 0, 				
	LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); 
    return hBitmap;
}